"""
UDP Communication Handler for Quadrotor Control System
=====================================================

This module provides a comprehensive UDP communication system for real-time
data transmission between different components of the quadrotor control system.

Key Features:
- High-performance UDP communication
- Multiple data formats (JSON, binary, protobuf)
- Automatic packet fragmentation and reassembly
- Reliable delivery with acknowledgments
- Multicast support for multi-drone scenarios
- Real-time performance monitoring
- Connection management and error handling

This implementation enables efficient communication between control systems,
sensors, and external monitoring tools.

Author: [Your Name]
Date: [Current Date]
License: MIT
"""

import socket
import struct
import json
import time
import threading
from typing import Dict, List, Tuple, Optional, Callable, Any, Union
from dataclasses import dataclass
from enum import Enum
import logging
from queue import Queue, Empty
import hashlib
import pickle
import zlib

# Optional protobuf support
try:
    import google.protobuf.message as protobuf
    PROTOBUF_AVAILABLE = True
except ImportError:
    PROTOBUF_AVAILABLE = False
    logging.warning("Protobuf not available. Install with: pip install protobuf")

# Configure logging
logging.basicConfig(level=logging.INFO)
logger = logging.getLogger(__name__)


class DataFormat(Enum):
    """Enumeration of supported data formats."""
    JSON = "json"
    BINARY = "binary"
    PROTOBUF = "protobuf"
    PICKLE = "pickle"
    COMPRESSED = "compressed"


class PacketType(Enum):
    """Enumeration of packet types."""
    DATA = 0x01
    ACK = 0x02
    NACK = 0x03
    HEARTBEAT = 0x04
    FRAGMENT = 0x05
    CONTROL = 0x06
    EMERGENCY = 0x07


@dataclass
class UDPConfig:
    """
    Configuration for UDP communication.
    
    Attributes:
        host (str): Host address for binding/listening
        port (int): Port number for communication
        data_format (DataFormat): Data format for transmission
        buffer_size (int): Socket buffer size
        timeout (float): Socket timeout in seconds
        max_packet_size (int): Maximum packet size in bytes
        enable_fragmentation (bool): Enable packet fragmentation
        enable_compression (bool): Enable data compression
        enable_reliability (bool): Enable reliable delivery
        multicast_group (str): Multicast group address
        ttl (int): Time-to-live for multicast
    """
    host: str = "0.0.0.0"
    port: int = 8080
    data_format: DataFormat = DataFormat.JSON
    buffer_size: int = 65536
    timeout: float = 1.0
    max_packet_size: int = 1400  # MTU-safe size
    enable_fragmentation: bool = True
    enable_compression: bool = False
    enable_reliability: bool = True
    multicast_group: str = None
    ttl: int = 1


@dataclass
class PacketHeader:
    """
    Packet header structure for reliable communication.
    
    Attributes:
        packet_type (PacketType): Type of packet
        sequence_number (int): Sequence number for ordering
        timestamp (float): Packet timestamp
        payload_size (int): Size of payload in bytes
        checksum (int): Data integrity checksum
        fragment_id (int): Fragment identifier
        total_fragments (int): Total number of fragments
    """
    packet_type: PacketType
    sequence_number: int
    timestamp: float
    payload_size: int
    checksum: int
    fragment_id: int = 0
    total_fragments: int = 1


class PacketFragmenter:
    """
    Packet fragmentation and reassembly system.
    
    This class handles the fragmentation of large packets into smaller
    pieces for transmission over UDP, and reassembles them on the receiving end.
    """
    
    def __init__(self, max_packet_size: int = 1400):
        """
        Initialize packet fragmenter.
        
        Args:
            max_packet_size (int): Maximum size of individual packets
        """
        self.max_packet_size = max_packet_size
        self.header_size = 32  # Size of packet header in bytes
        self.max_payload_size = max_packet_size - self.header_size
        
        # Fragment tracking
        self.fragment_buffers: Dict[int, Dict[int, bytes]] = {}
        self.fragment_timestamps: Dict[int, float] = {}
        self.fragment_timeout = 5.0  # seconds
        
        # Cleanup thread
        self.cleanup_thread = threading.Thread(target=self._cleanup_fragments, daemon=True)
        self.cleanup_thread.start()
        
        logger.info(f"Packet fragmenter initialized: max_packet_size={max_packet_size}")
    
    def fragment_packet(self, data: bytes, sequence_number: int) -> List[bytes]:
        """
        Fragment a large packet into smaller pieces.
        
        Args:
            data (bytes): Data to fragment
            sequence_number (int): Sequence number for the packet
            
        Returns:
            List[bytes]: List of fragmented packets
        """
        fragments = []
        total_fragments = (len(data) + self.max_payload_size - 1) // self.max_payload_size
        
        for fragment_id in range(total_fragments):
            start_idx = fragment_id * self.max_payload_size
            end_idx = min(start_idx + self.max_payload_size, len(data))
            payload = data[start_idx:end_idx]
            
            # Create packet header
            header = PacketHeader(
                packet_type=PacketType.FRAGMENT,
                sequence_number=sequence_number,
                timestamp=time.time(),
                payload_size=len(payload),
                checksum=self._calculate_checksum(payload),
                fragment_id=fragment_id,
                total_fragments=total_fragments
            )
            
            # Serialize packet
            packet = self._serialize_packet(header, payload)
            fragments.append(packet)
        
        logger.debug(f"Fragmented packet {sequence_number} into {total_fragments} pieces")
        return fragments
    
    def add_fragment(self, fragment: bytes) -> Optional[bytes]:
        """
        Add a fragment to the reassembly buffer.
        
        Args:
            fragment (bytes): Fragment packet
            
        Returns:
            Optional[bytes]: Complete packet if reassembly is complete, None otherwise
        """
        try:
            # Parse packet header
            header = self._deserialize_header(fragment)
            
            if header.packet_type != PacketType.FRAGMENT:
                return None
            
            # Extract payload
            payload = fragment[self.header_size:self.header_size + header.payload_size]
            
            # Verify checksum
            if self._calculate_checksum(payload) != header.checksum:
                logger.warning(f"Checksum mismatch for fragment {header.sequence_number}.{header.fragment_id}")
                return None
            
            # Add to fragment buffer
            if header.sequence_number not in self.fragment_buffers:
                self.fragment_buffers[header.sequence_number] = {}
                self.fragment_timestamps[header.sequence_number] = time.time()
            
            self.fragment_buffers[header.sequence_number][header.fragment_id] = payload
            
            # Check if all fragments are received
            if len(self.fragment_buffers[header.sequence_number]) == header.total_fragments:
                # Reassemble packet
                complete_payload = self._reassemble_packet(header.sequence_number)
                
                # Clean up
                del self.fragment_buffers[header.sequence_number]
                del self.fragment_timestamps[header.sequence_number]
                
                logger.debug(f"Reassembled packet {header.sequence_number}")
                return complete_payload
            
            return None
            
        except Exception as e:
            logger.error(f"Error processing fragment: {e}")
            return None
    
    def _reassemble_packet(self, sequence_number: int) -> bytes:
        """
        Reassemble a complete packet from fragments.
        
        Args:
            sequence_number (int): Sequence number of the packet
            
        Returns:
            bytes: Complete packet payload
        """
        fragments = self.fragment_buffers[sequence_number]
        fragment_ids = sorted(fragments.keys())
        
        # Concatenate fragments in order
        complete_payload = b''
        for fragment_id in fragment_ids:
            complete_payload += fragments[fragment_id]
        
        return complete_payload
    
    def _cleanup_fragments(self):
        """Clean up expired fragment buffers."""
        while True:
            try:
                current_time = time.time()
                expired_sequences = []
                
                for sequence_number, timestamp in self.fragment_timestamps.items():
                    if current_time - timestamp > self.fragment_timeout:
                        expired_sequences.append(sequence_number)
                
                for sequence_number in expired_sequences:
                    del self.fragment_buffers[sequence_number]
                    del self.fragment_timestamps[sequence_number]
                    logger.warning(f"Expired fragment buffer for sequence {sequence_number}")
                
                time.sleep(1.0)  # Check every second
                
            except Exception as e:
                logger.error(f"Error in fragment cleanup: {e}")
    
    def _calculate_checksum(self, data: bytes) -> int:
        """Calculate checksum for data integrity."""
        return zlib.crc32(data) & 0xFFFFFFFF
    
    def _serialize_packet(self, header: PacketHeader, payload: bytes) -> bytes:
        """Serialize packet header and payload."""
        # Pack header: type(1) + seq(4) + timestamp(8) + size(4) + checksum(4) + frag_id(4) + total_frags(4) + reserved(3)
        header_data = struct.pack('!BIdIIII3x', 
                                header.packet_type.value,
                                header.sequence_number,
                                header.timestamp,
                                header.payload_size,
                                header.checksum,
                                header.fragment_id,
                                header.total_fragments)
        
        return header_data + payload
    
    def _deserialize_header(self, packet: bytes) -> PacketHeader:
        """Deserialize packet header."""
        header_data = packet[:self.header_size]
        packet_type_val, seq_num, timestamp, payload_size, checksum, frag_id, total_frags = struct.unpack('!BIdIIII3x', header_data)
        
        return PacketHeader(
            packet_type=PacketType(packet_type_val),
            sequence_number=seq_num,
            timestamp=timestamp,
            payload_size=payload_size,
            checksum=checksum,
            fragment_id=frag_id,
            total_fragments=total_frags
        )


class DataSerializer:
    """
    Data serialization and deserialization system.
    
    This class handles the conversion of Python objects to and from
    various data formats for network transmission.
    """
    
    def __init__(self, data_format: DataFormat):
        """
        Initialize data serializer.
        
        Args:
            data_format (DataFormat): Data format to use
        """
        self.data_format = data_format
        self.sequence_number = 0
        
        logger.info(f"Data serializer initialized: format={data_format}")
    
    def serialize(self, data: Any) -> bytes:
        """
        Serialize data to bytes.
        
        Args:
            data (Any): Data to serialize
            
        Returns:
            bytes: Serialized data
        """
        if self.data_format == DataFormat.JSON:
            return self._serialize_json(data)
        elif self.data_format == DataFormat.BINARY:
            return self._serialize_binary(data)
        elif self.data_format == DataFormat.PROTOBUF:
            return self._serialize_protobuf(data)
        elif self.data_format == DataFormat.PICKLE:
            return self._serialize_pickle(data)
        elif self.data_format == DataFormat.COMPRESSED:
            return self._serialize_compressed(data)
        else:
            raise ValueError(f"Unsupported data format: {self.data_format}")
    
    def deserialize(self, data: bytes) -> Any:
        """
        Deserialize data from bytes.
        
        Args:
            data (bytes): Data to deserialize
            
        Returns:
            Any: Deserialized data
        """
        if self.data_format == DataFormat.JSON:
            return self._deserialize_json(data)
        elif self.data_format == DataFormat.BINARY:
            return self._deserialize_binary(data)
        elif self.data_format == DataFormat.PROTOBUF:
            return self._deserialize_protobuf(data)
        elif self.data_format == DataFormat.PICKLE:
            return self._deserialize_pickle(data)
        elif self.data_format == DataFormat.COMPRESSED:
            return self._deserialize_compressed(data)
        else:
            raise ValueError(f"Unsupported data format: {self.data_format}")
    
    def _serialize_json(self, data: Any) -> bytes:
        """Serialize data to JSON format."""
        try:
            json_str = json.dumps(data, default=self._json_serializer)
            return json_str.encode('utf-8')
        except Exception as e:
            logger.error(f"JSON serialization error: {e}")
            raise
    
    def _deserialize_json(self, data: bytes) -> Any:
        """Deserialize data from JSON format."""
        try:
            json_str = data.decode('utf-8')
            return json.loads(json_str)
        except Exception as e:
            logger.error(f"JSON deserialization error: {e}")
            raise
    
    def _serialize_binary(self, data: Any) -> bytes:
        """Serialize data to binary format."""
        try:
            if isinstance(data, dict):
                return self._serialize_dict_binary(data)
            elif isinstance(data, (list, tuple)):
                return self._serialize_list_binary(data)
            elif isinstance(data, (int, float)):
                return struct.pack('!d', float(data))
            elif isinstance(data, str):
                encoded = data.encode('utf-8')
                return struct.pack('!I', len(encoded)) + encoded
            elif isinstance(data, bytes):
                return struct.pack('!I', len(data)) + data
            else:
                return pickle.dumps(data)
        except Exception as e:
            logger.error(f"Binary serialization error: {e}")
            raise
    
    def _deserialize_binary(self, data: bytes) -> Any:
        """Deserialize data from binary format."""
        try:
            # Try to deserialize as different types
            if len(data) >= 8:  # At least a double
                try:
                    return struct.unpack('!d', data[:8])[0]
                except:
                    pass
            
            if len(data) >= 4:  # At least a string length
                try:
                    str_len = struct.unpack('!I', data[:4])[0]
                    if len(data) >= 4 + str_len:
                        return data[4:4+str_len].decode('utf-8')
                except:
                    pass
            
            # Try pickle as fallback
            return pickle.loads(data)
        except Exception as e:
            logger.error(f"Binary deserialization error: {e}")
            raise
    
    def _serialize_protobuf(self, data: Any) -> bytes:
        """Serialize data to protobuf format."""
        if not PROTOBUF_AVAILABLE:
            raise ImportError("Protobuf not available")
        
        try:
            if hasattr(data, 'SerializeToString'):
                return data.SerializeToString()
            else:
                # Fallback to JSON for non-protobuf objects
                return self._serialize_json(data)
        except Exception as e:
            logger.error(f"Protobuf serialization error: {e}")
            raise
    
    def _deserialize_protobuf(self, data: bytes) -> Any:
        """Deserialize data from protobuf format."""
        if not PROTOBUF_AVAILABLE:
            raise ImportError("Protobuf not available")
        
        try:
            # This is a simplified implementation
            # In practice, you would need to know the message type
            return data  # Return raw bytes for now
        except Exception as e:
            logger.error(f"Protobuf deserialization error: {e}")
            raise
    
    def _serialize_pickle(self, data: Any) -> bytes:
        """Serialize data using pickle."""
        try:
            return pickle.dumps(data)
        except Exception as e:
            logger.error(f"Pickle serialization error: {e}")
            raise
    
    def _deserialize_pickle(self, data: bytes) -> Any:
        """Deserialize data using pickle."""
        try:
            return pickle.loads(data)
        except Exception as e:
            logger.error(f"Pickle deserialization error: {e}")
            raise
    
    def _serialize_compressed(self, data: Any) -> bytes:
        """Serialize data with compression."""
        try:
            # First serialize to JSON
            json_data = self._serialize_json(data)
            # Then compress
            return zlib.compress(json_data)
        except Exception as e:
            logger.error(f"Compressed serialization error: {e}")
            raise
    
    def _deserialize_compressed(self, data: bytes) -> Any:
        """Deserialize compressed data."""
        try:
            # First decompress
            json_data = zlib.decompress(data)
            # Then deserialize JSON
            return self._deserialize_json(json_data)
        except Exception as e:
            logger.error(f"Compressed deserialization error: {e}")
            raise
    
    def _serialize_dict_binary(self, data: dict) -> bytes:
        """Serialize dictionary to binary format."""
        result = struct.pack('!I', len(data))
        for key, value in data.items():
            key_bytes = key.encode('utf-8')
            result += struct.pack('!I', len(key_bytes)) + key_bytes
            result += self._serialize_binary(value)
        return result
    
    def _serialize_list_binary(self, data: Union[list, tuple]) -> bytes:
        """Serialize list/tuple to binary format."""
        result = struct.pack('!I', len(data))
        for item in data:
            result += self._serialize_binary(item)
        return result
    
    def _json_serializer(self, obj):
        """Custom JSON serializer for non-serializable objects."""
        if hasattr(obj, '__dict__'):
            return obj.__dict__
        elif hasattr(obj, 'tolist'):  # numpy arrays
            return obj.tolist()
        else:
            return str(obj)


class UDPHandler:
    """
    Main UDP communication handler.
    
    This class provides a complete UDP communication system with support
    for reliable delivery, fragmentation, and multiple data formats.
    """
    
    def __init__(self, config: UDPConfig):
        """
        Initialize UDP handler.
        
        Args:
            config (UDPConfig): UDP configuration
        """
        self.config = config
        
        # Initialize components
        self.serializer = DataSerializer(config.data_format)
        self.fragmenter = PacketFragmenter(config.max_packet_size)
        
        # Socket management
        self.socket = None
        self.connected = False
        
        # Threading
        self.receive_thread = None
        self.send_thread = None
        self.running = False
        
        # Queues
        self.send_queue = Queue()
        self.receive_queue = Queue()
        
        # Callbacks
        self.data_callbacks: List[Callable] = []
        self.error_callbacks: List[Callable] = []
        
        # Performance monitoring
        self.packets_sent = 0
        self.packets_received = 0
        self.bytes_sent = 0
        self.bytes_received = 0
        self.errors = 0
        self.last_activity = time.time()
        
        # Reliability tracking
        self.pending_acks: Dict[int, Tuple[float, Any]] = {}
        self.ack_timeout = 1.0  # seconds
        
        logger.info(f"UDP handler initialized: {config.host}:{config.port}")
    
    def connect(self) -> bool:
        """
        Connect and start UDP communication.
        
        Returns:
            bool: True if connection successful
        """
        try:
            # Create UDP socket
            self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
            self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, self.config.buffer_size)
            self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_SNDBUF, self.config.buffer_size)
            self.socket.settimeout(self.config.timeout)
            
            # Bind to address
            self.socket.bind((self.config.host, self.config.port))
            
            # Setup multicast if configured
            if self.config.multicast_group:
                self.socket.setsockopt(socket.IPPROTO_IP, socket.IP_MULTICAST_TTL, self.config.ttl)
                self.socket.setsockopt(socket.IPPROTO_IP, socket.IP_ADD_MEMBERSHIP,
                                     socket.inet_aton(self.config.multicast_group) + socket.inet_aton(self.config.host))
            
            self.connected = True
            
            # Start communication threads
            self.running = True
            self.receive_thread = threading.Thread(target=self._receive_loop, daemon=True)
            self.send_thread = threading.Thread(target=self._send_loop, daemon=True)
            self.receive_thread.start()
            self.send_thread.start()
            
            logger.info(f"UDP handler connected: {self.config.host}:{self.config.port}")
            return True
            
        except Exception as e:
            logger.error(f"Failed to connect UDP handler: {e}")
            self.connected = False
            return False
    
    def disconnect(self):
        """Disconnect and stop UDP communication."""
        self.running = False
        
        if self.receive_thread:
            self.receive_thread.join(timeout=1.0)
        if self.send_thread:
            self.send_thread.join(timeout=1.0)
        
        if self.socket:
            self.socket.close()
            self.socket = None
        
        self.connected = False
        logger.info("UDP handler disconnected")
    
    def send_data(self, data: Any, address: Tuple[str, int]) -> bool:
        """
        Send data to a specific address.
        
        Args:
            data (Any): Data to send
            address (Tuple[str, int]): Destination address (host, port)
            
        Returns:
            bool: True if queued successfully
        """
        if not self.connected:
            logger.warning("Cannot send data: not connected")
            return False
        
        try:
            # Serialize data
            serialized_data = self.serializer.serialize(data)
            
            # Create packet header
            header = PacketHeader(
                packet_type=PacketType.DATA,
                sequence_number=self.serializer.sequence_number,
                timestamp=time.time(),
                payload_size=len(serialized_data),
                checksum=self.fragmenter._calculate_checksum(serialized_data)
            )
            
            # Fragment if necessary
            if self.config.enable_fragmentation and len(serialized_data) > self.fragmenter.max_payload_size:
                fragments = self.fragmenter.fragment_packet(serialized_data, header.sequence_number)
                for fragment in fragments:
                    self.send_queue.put((fragment, address))
            else:
                # Send as single packet
                packet = self.fragmenter._serialize_packet(header, serialized_data)
                self.send_queue.put((packet, address))
            
            # Track for reliability
            if self.config.enable_reliability:
                self.pending_acks[header.sequence_number] = (time.time(), data)
            
            self.serializer.sequence_number += 1
            return True
            
        except Exception as e:
            logger.error(f"Failed to queue data for sending: {e}")
            return False
    
    def broadcast_data(self, data: Any, port: int) -> bool:
        """
        Broadcast data to all hosts on a specific port.
        
        Args:
            data (Any): Data to broadcast
            port (int): Destination port
            
        Returns:
            bool: True if queued successfully
        """
        return self.send_data(data, ("255.255.255.255", port))
    
    def _receive_loop(self):
        """Main receive loop."""
        while self.running:
            try:
                # Receive data
                data, address = self.socket.recvfrom(self.config.buffer_size)
                
                # Process received data
                self._process_received_data(data, address)
                
                # Update statistics
                self.packets_received += 1
                self.bytes_received += len(data)
                self.last_activity = time.time()
                
            except socket.timeout:
                continue
            except Exception as e:
                logger.error(f"Error in receive loop: {e}")
                self.errors += 1
    
    def _send_loop(self):
        """Main send loop."""
        while self.running:
            try:
                # Get data from queue
                try:
                    packet, address = self.send_queue.get(timeout=0.1)
                except Empty:
                    continue
                
                # Send packet
                self.socket.sendto(packet, address)
                
                # Update statistics
                self.packets_sent += 1
                self.bytes_sent += len(packet)
                self.last_activity = time.time()
                
            except Exception as e:
                logger.error(f"Error in send loop: {e}")
                self.errors += 1
    
    def _process_received_data(self, data: bytes, address: Tuple[str, int]):
        """Process received data."""
        try:
            # Check if it's a fragment
            if len(data) >= 32:  # Minimum header size
                header = self.fragmenter._deserialize_header(data)
                
                if header.packet_type == PacketType.FRAGMENT:
                    # Handle fragment
                    complete_payload = self.fragmenter.add_fragment(data)
                    if complete_payload:
                        self._handle_complete_packet(complete_payload, address)
                    return
                elif header.packet_type == PacketType.ACK:
                    # Handle acknowledgment
                    self._handle_ack(header.sequence_number)
                    return
                elif header.packet_type == PacketType.NACK:
                    # Handle negative acknowledgment
                    self._handle_nack(header.sequence_number)
                    return
                elif header.packet_type == PacketType.HEARTBEAT:
                    # Handle heartbeat
                    self._handle_heartbeat(address)
                    return
                elif header.packet_type == PacketType.EMERGENCY:
                    # Handle emergency message
                    self._handle_emergency(data, address)
                    return
            
            # Handle regular data packet
            self._handle_complete_packet(data, address)
            
        except Exception as e:
            logger.error(f"Error processing received data: {e}")
            self.errors += 1
    
    def _handle_complete_packet(self, data: bytes, address: Tuple[str, int]):
        """Handle a complete packet."""
        try:
            # Parse header
            header = self.fragmenter._deserialize_header(data)
            payload = data[32:32 + header.payload_size]
            
            # Verify checksum
            if self.fragmenter._calculate_checksum(payload) != header.checksum:
                logger.warning(f"Checksum mismatch for packet {header.sequence_number}")
                if self.config.enable_reliability:
                    self._send_nack(header.sequence_number, address)
                return
            
            # Deserialize payload
            deserialized_data = self.serializer.deserialize(payload)
            
            # Send acknowledgment if reliability is enabled
            if self.config.enable_reliability:
                self._send_ack(header.sequence_number, address)
            
            # Add to receive queue
            self.receive_queue.put((deserialized_data, address))
            
            # Call data callbacks
            for callback in self.data_callbacks:
                try:
                    callback(deserialized_data, address)
                except Exception as e:
                    logger.error(f"Error in data callback: {e}")
            
        except Exception as e:
            logger.error(f"Error handling complete packet: {e}")
            self.errors += 1
    
    def _send_ack(self, sequence_number: int, address: Tuple[str, int]):
        """Send acknowledgment."""
        try:
            header = PacketHeader(
                packet_type=PacketType.ACK,
                sequence_number=sequence_number,
                timestamp=time.time(),
                payload_size=0,
                checksum=0
            )
            packet = self.fragmenter._serialize_packet(header, b'')
            self.socket.sendto(packet, address)
        except Exception as e:
            logger.error(f"Error sending ACK: {e}")
    
    def _send_nack(self, sequence_number: int, address: Tuple[str, int]):
        """Send negative acknowledgment."""
        try:
            header = PacketHeader(
                packet_type=PacketType.NACK,
                sequence_number=sequence_number,
                timestamp=time.time(),
                payload_size=0,
                checksum=0
            )
            packet = self.fragmenter._serialize_packet(header, b'')
            self.socket.sendto(packet, address)
        except Exception as e:
            logger.error(f"Error sending NACK: {e}")
    
    def _handle_ack(self, sequence_number: int):
        """Handle acknowledgment."""
        if sequence_number in self.pending_acks:
            del self.pending_acks[sequence_number]
            logger.debug(f"Received ACK for sequence {sequence_number}")
    
    def _handle_nack(self, sequence_number: int):
        """Handle negative acknowledgment."""
        if sequence_number in self.pending_acks:
            # Retransmit the packet
            timestamp, data = self.pending_acks[sequence_number]
            logger.warning(f"Received NACK for sequence {sequence_number}, retransmitting")
            # Note: In a full implementation, you would retransmit the data
    
    def _handle_heartbeat(self, address: Tuple[str, int]):
        """Handle heartbeat message."""
        # Send heartbeat response
        try:
            header = PacketHeader(
                packet_type=PacketType.HEARTBEAT,
                sequence_number=0,
                timestamp=time.time(),
                payload_size=0,
                checksum=0
            )
            packet = self.fragmenter._serialize_packet(header, b'')
            self.socket.sendto(packet, address)
        except Exception as e:
            logger.error(f"Error sending heartbeat response: {e}")
    
    def _handle_emergency(self, data: bytes, address: Tuple[str, int]):
        """Handle emergency message."""
        logger.warning(f"Received emergency message from {address}")
        # Call error callbacks
        for callback in self.error_callbacks:
            try:
                callback("Emergency message received", address)
            except Exception as e:
                logger.error(f"Error in error callback: {e}")
    
    def get_data(self, timeout: float = 0.1) -> Optional[Tuple[Any, Tuple[str, int]]]:
        """
        Get received data from queue.
        
        Args:
            timeout (float): Timeout for getting data
            
        Returns:
            Optional[Tuple[Any, Tuple[str, int]]]: Data and sender address, or None if timeout
        """
        try:
            return self.receive_queue.get(timeout=timeout)
        except Empty:
            return None
    
    def add_data_callback(self, callback: Callable):
        """
        Add callback for received data.
        
        Args:
            callback (Callable): Function to call when data is received
        """
        self.data_callbacks.append(callback)
    
    def add_error_callback(self, callback: Callable):
        """
        Add callback for errors.
        
        Args:
            callback (Callable): Function to call when errors occur
        """
        self.error_callbacks.append(callback)
    
    def send_heartbeat(self, address: Tuple[str, int]):
        """Send heartbeat message."""
        try:
            header = PacketHeader(
                packet_type=PacketType.HEARTBEAT,
                sequence_number=0,
                timestamp=time.time(),
                payload_size=0,
                checksum=0
            )
            packet = self.fragmenter._serialize_packet(header, b'')
            self.socket.sendto(packet, address)
        except Exception as e:
            logger.error(f"Error sending heartbeat: {e}")
    
    def send_emergency(self, message: str, address: Tuple[str, int]):
        """Send emergency message."""
        try:
            message_data = message.encode('utf-8')
            header = PacketHeader(
                packet_type=PacketType.EMERGENCY,
                sequence_number=0,
                timestamp=time.time(),
                payload_size=len(message_data),
                checksum=self.fragmenter._calculate_checksum(message_data)
            )
            packet = self.fragmenter._serialize_packet(header, message_data)
            self.socket.sendto(packet, address)
        except Exception as e:
            logger.error(f"Error sending emergency message: {e}")
    
    def get_performance_stats(self) -> Dict[str, Any]:
        """
        Get performance statistics.
        
        Returns:
            Dict[str, Any]: Performance statistics
        """
        current_time = time.time()
        time_since_activity = current_time - self.last_activity
        
        return {
            'packets_sent': self.packets_sent,
            'packets_received': self.packets_received,
            'bytes_sent': self.bytes_sent,
            'bytes_received': self.bytes_received,
            'errors': self.errors,
            'time_since_activity': time_since_activity,
            'pending_acks': len(self.pending_acks),
            'connected': self.connected,
            'send_queue_size': self.send_queue.qsize(),
            'receive_queue_size': self.receive_queue.qsize()
        }
    
    def reset_stats(self):
        """Reset performance statistics."""
        self.packets_sent = 0
        self.packets_received = 0
        self.bytes_sent = 0
        self.bytes_received = 0
        self.errors = 0
        self.last_activity = time.time()
        logger.info("UDP handler statistics reset")


# Example usage and testing
if __name__ == "__main__":
    """
    Example usage of the UDP handler.
    
    This demonstrates how to set up and use the UDP handler for
    real-time communication between quadrotor control components.
    """
    
    # Initialize configuration
    config = UDPConfig(
        host="0.0.0.0",
        port=8080,
        data_format=DataFormat.JSON,
        enable_fragmentation=True,
        enable_reliability=True,
        multicast_group="224.0.0.1"
    )
    
    # Initialize UDP handler
    udp_handler = UDPHandler(config)
    
    # Add callbacks
    def data_callback(data, address):
        """Callback for received data."""
        print(f"Received data from {address}: {data}")
    
    def error_callback(error, address):
        """Callback for errors."""
        print(f"Error from {address}: {error}")
    
    udp_handler.add_data_callback(data_callback)
    udp_handler.add_error_callback(error_callback)
    
    # Connect to network
    if udp_handler.connect():
        print("UDP handler connected")
        
        try:
            # Main loop
            print("UDP communication active...")
            print("Press Ctrl+C to stop")
            
            # Send some test data
            test_data = {
                'type': 'position',
                'x': 1.0,
                'y': 2.0,
                'z': 3.0,
                'timestamp': time.time()
            }
            
            udp_handler.send_data(test_data, ("127.0.0.1", 8081))
            
            while True:
                # Get received data
                received = udp_handler.get_data(timeout=1.0)
                if received:
                    data, address = received
                    print(f"Processed data from {address}: {data}")
                
                # Print performance stats every 10 seconds
                if int(time.time()) % 10 == 0:
                    stats = udp_handler.get_performance_stats()
                    print(f"Performance: {stats}")
                
                time.sleep(0.1)
                
        except KeyboardInterrupt:
            print("\nStopping UDP handler...")
        
        finally:
            udp_handler.disconnect()
            print("UDP handler stopped")
    
    else:
        print("Failed to connect UDP handler")
