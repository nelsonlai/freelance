"""
Natural Language Processing Applications of Hashing
==================================================

This file demonstrates how hashing is used in Natural Language Processing:
- Word frequency analysis
- Document similarity with MinHash
- N-gram analysis
- Spell checking
- Text preprocessing and tokenization
- Vocabulary building

These applications show how hashing enables efficient text processing
and analysis in modern NLP systems.

Author: Hash Lecture Series
Purpose: Educational demonstration of hashing in NLP applications
"""

import hashlib
import re
import math
from collections import defaultdict, Counter
from typing import List, Dict, Set, Tuple, Any


class WordFrequencyAnalyzer:
    """
    Word frequency analysis using hash tables.
    
    This class demonstrates how to efficiently count word frequencies
    in text documents using hash tables for O(1) average-case performance.
    
    Applications:
    - Text analysis
    - Keyword extraction
    - Language modeling
    - Content analysis
    """
    
    def __init__(self):
        """
        Initialize the word frequency analyzer.
        """
        self.word_counts = defaultdict(int)
        self.total_words = 0
        self.stop_words = self._load_stop_words()
    
    def _load_stop_words(self) -> Set[str]:
        """
        Load common stop words that are typically filtered out.
        
        Returns:
            Set of stop words
        """
        return {
            'a', 'an', 'and', 'are', 'as', 'at', 'be', 'by', 'for', 'from',
            'has', 'he', 'in', 'is', 'it', 'its', 'of', 'on', 'that', 'the',
            'to', 'was', 'will', 'with', 'i', 'you', 'we', 'they', 'this',
            'these', 'those', 'or', 'but', 'if', 'when', 'where', 'why',
            'how', 'what', 'who', 'which', 'there', 'here', 'can', 'could',
            'should', 'would', 'may', 'might', 'must', 'shall'
        }
    
    def preprocess_text(self, text: str) -> List[str]:
        """
        Preprocess text by cleaning and tokenizing.
        
        Args:
            text: Raw text to preprocess
            
        Returns:
            List of cleaned tokens
        """
        # Convert to lowercase
        text = text.lower()
        
        # Remove punctuation and split into words
        # Keep only alphanumeric characters and spaces
        text = re.sub(r'[^a-z0-9\s]', ' ', text)
        
        # Split into words and remove empty strings
        words = [word for word in text.split() if word]
        
        return words
    
    def add_text(self, text: str, filter_stop_words: bool = True) -> None:
        """
        Add text to the frequency analysis.
        
        Args:
            text: Text to analyze
            filter_stop_words: Whether to filter out stop words
        """
        words = self.preprocess_text(text)
        
        for word in words:
            # Filter stop words if requested
            if filter_stop_words and word in self.stop_words:
                continue
            
            # Increment word count using hash table
            self.word_counts[word] += 1
            self.total_words += 1
    
    def get_word_frequency(self, word: str) -> int:
        """
        Get the frequency of a specific word.
        
        Args:
            word: The word to look up
            
        Returns:
            Frequency count of the word
        """
        return self.word_counts.get(word.lower(), 0)
    
    def get_top_words(self, n: int = 10) -> List[Tuple[str, int]]:
        """
        Get the top N most frequent words.
        
        Args:
            n: Number of top words to return
            
        Returns:
            List of (word, frequency) tuples sorted by frequency
        """
        return Counter(self.word_counts).most_common(n)
    
    def get_word_probability(self, word: str) -> float:
        """
        Get the probability of a word in the corpus.
        
        Args:
            word: The word to get probability for
            
        Returns:
            Probability of the word (frequency / total words)
        """
        if self.total_words == 0:
            return 0.0
        
        return self.get_word_frequency(word) / self.total_words
    
    def calculate_tf_idf(self, word: str, document_count: int) -> float:
        """
        Calculate TF-IDF (Term Frequency-Inverse Document Frequency) for a word.
        
        Args:
            word: The word to calculate TF-IDF for
            document_count: Total number of documents
            
        Returns:
            TF-IDF score
        """
        # Term Frequency (TF)
        tf = self.get_word_frequency(word)
        
        # Document Frequency (DF) - simplified as word frequency here
        df = self.get_word_frequency(word)
        
        # Inverse Document Frequency (IDF)
        if df == 0:
            return 0.0
        
        idf = math.log(document_count / df)
        
        # TF-IDF = TF * IDF
        return tf * idf
    
    def display_statistics(self) -> None:
        """Display analysis statistics."""
        print(f"Word Frequency Analysis Statistics:")
        print(f"  Total unique words: {len(self.word_counts)}")
        print(f"  Total word count: {self.total_words}")
        print(f"  Average frequency: {self.total_words / len(self.word_counts) if self.word_counts else 0:.2f}")
        
        print(f"\nTop 10 most frequent words:")
        top_words = self.get_top_words(10)
        for i, (word, count) in enumerate(top_words, 1):
            print(f"  {i:2d}. {word:<15} : {count:4d} ({count/self.total_words*100:.2f}%)")


class MinHashDocumentSimilarity:
    """
    Document similarity using MinHash algorithm.
    
    MinHash is used to estimate the Jaccard similarity between documents
    efficiently, which is useful for:
    - Document clustering
    - Plagiarism detection
    - Recommendation systems
    - Duplicate detection
    """
    
    def __init__(self, num_hashes: int = 100):
        """
        Initialize MinHash document similarity analyzer.
        
        Args:
            num_hashes: Number of hash functions to use (more = more accurate)
        """
        self.num_hashes = num_hashes
        self.documents = {}
    
    def _create_shingles(self, text: str, k: int = 3) -> Set[str]:
        """
        Create k-shingles from text.
        
        Shingles are contiguous substrings of length k.
        They capture local patterns in text.
        
        Args:
            text: Text to create shingles from
            k: Length of shingles
            
        Returns:
            Set of k-shingles
        """
        # Clean text and remove spaces for shingle creation
        text = re.sub(r'[^a-z0-9]', '', text.lower())
        
        shingles = set()
        for i in range(len(text) - k + 1):
            shingle = text[i:i + k]
            if len(shingle) == k:  # Ensure we have exactly k characters
                shingles.add(shingle)
        
        return shingles
    
    def _minhash_signature(self, shingles: Set[str]) -> List[int]:
        """
        Create MinHash signature for a set of shingles.
        
        Args:
            shingles: Set of shingles
            
        Returns:
            MinHash signature (list of minimum hash values)
        """
        signature = []
        
        for i in range(self.num_hashes):
            min_hash = float('inf')
            
            for shingle in shingles:
                # Create hash with seed for different hash functions
                hash_value = int(hashlib.md5(f"{shingle}{i}".encode()).hexdigest(), 16)
                min_hash = min(min_hash, hash_value)
            
            signature.append(min_hash)
        
        return signature
    
    def add_document(self, doc_id: str, text: str, k: int = 3) -> None:
        """
        Add a document to the similarity analysis.
        
        Args:
            doc_id: Unique identifier for the document
            text: Document text
            k: Shingle size
        """
        shingles = self._create_shingles(text, k)
        signature = self._minhash_signature(shingles)
        
        self.documents[doc_id] = {
            'text': text,
            'shingles': shingles,
            'signature': signature
        }
    
    def jaccard_similarity(self, doc1_id: str, doc2_id: str) -> float:
        """
        Calculate Jaccard similarity between two documents.
        
        Args:
            doc1_id: First document ID
            doc2_id: Second document ID
            
        Returns:
            Jaccard similarity (0.0 to 1.0)
        """
        if doc1_id not in self.documents or doc2_id not in self.documents:
            return 0.0
        
        doc1 = self.documents[doc1_id]
        doc2 = self.documents[doc2_id]
        
        # Calculate actual Jaccard similarity using shingles
        intersection = len(doc1['shingles'] & doc2['shingles'])
        union = len(doc1['shingles'] | doc2['shingles'])
        
        if union == 0:
            return 0.0
        
        return intersection / union
    
    def estimated_jaccard_similarity(self, doc1_id: str, doc2_id: str) -> float:
        """
        Estimate Jaccard similarity using MinHash signatures.
        
        Args:
            doc1_id: First document ID
            doc2_id: Second document ID
            
        Returns:
            Estimated Jaccard similarity (0.0 to 1.0)
        """
        if doc1_id not in self.documents or doc2_id not in self.documents:
            return 0.0
        
        doc1 = self.documents[doc1_id]
        doc2 = self.documents[doc2_id]
        
        # Count matching hash values in signatures
        matches = sum(1 for a, b in zip(doc1['signature'], doc2['signature']) if a == b)
        
        return matches / self.num_hashes
    
    def find_similar_documents(self, doc_id: str, threshold: float = 0.5) -> List[Tuple[str, float]]:
        """
        Find documents similar to a given document.
        
        Args:
            doc_id: Document to find similar documents for
            threshold: Minimum similarity threshold
            
        Returns:
            List of (document_id, similarity) tuples
        """
        similar_docs = []
        
        for other_doc_id in self.documents:
            if other_doc_id != doc_id:
                similarity = self.estimated_jaccard_similarity(doc_id, other_doc_id)
                if similarity >= threshold:
                    similar_docs.append((other_doc_id, similarity))
        
        # Sort by similarity (descending)
        similar_docs.sort(key=lambda x: x[1], reverse=True)
        
        return similar_docs


class NGramAnalyzer:
    """
    N-gram analysis using hash tables.
    
    N-grams are contiguous sequences of n items from a given text.
    They are useful for:
    - Language modeling
    - Text generation
    - Pattern recognition
    - Machine translation
    """
    
    def __init__(self, n: int = 2):
        """
        Initialize N-gram analyzer.
        
        Args:
            n: Size of n-grams (bigrams=2, trigrams=3, etc.)
        """
        self.n = n
        self.ngram_counts = defaultdict(int)
        self.total_ngrams = 0
    
    def add_text(self, text: str) -> None:
        """
        Add text to the N-gram analysis.
        
        Args:
            text: Text to analyze
        """
        words = text.lower().split()
        
        # Create n-grams
        for i in range(len(words) - self.n + 1):
            ngram = tuple(words[i:i + self.n])
            self.ngram_counts[ngram] += 1
            self.total_ngrams += 1
    
    def get_ngram_frequency(self, ngram: Tuple[str, ...]) -> int:
        """
        Get the frequency of a specific n-gram.
        
        Args:
            ngram: The n-gram to look up
            
        Returns:
            Frequency count of the n-gram
        """
        return self.ngram_counts.get(ngram, 0)
    
    def get_top_ngrams(self, n: int = 10) -> List[Tuple[Tuple[str, ...], int]]:
        """
        Get the top N most frequent n-grams.
        
        Args:
            n: Number of top n-grams to return
            
        Returns:
            List of (ngram, frequency) tuples sorted by frequency
        """
        return Counter(self.ngram_counts).most_common(n)
    
    def predict_next_word(self, context: str) -> List[Tuple[str, float]]:
        """
        Predict the next word based on context using n-grams.
        
        Args:
            context: Context words (should be n-1 words)
            
        Returns:
            List of (word, probability) tuples
        """
        context_words = context.lower().split()
        
        if len(context_words) < self.n - 1:
            return []
        
        # Get the last n-1 words as context
        context_tuple = tuple(context_words[-(self.n-1):])
        
        # Find all n-grams that start with this context
        candidates = {}
        for ngram, count in self.ngram_counts.items():
            if ngram[:self.n-1] == context_tuple:
                next_word = ngram[-1]
                candidates[next_word] = candidates.get(next_word, 0) + count
        
        # Convert counts to probabilities
        total_context_count = sum(candidates.values())
        if total_context_count == 0:
            return []
        
        predictions = []
        for word, count in candidates.items():
            probability = count / total_context_count
            predictions.append((word, probability))
        
        # Sort by probability (descending)
        predictions.sort(key=lambda x: x[1], reverse=True)
        
        return predictions


class SpellChecker:
    """
    Spell checker using hash tables for dictionary lookup.
    
    This implementation demonstrates how to use hash tables for
    efficient spell checking and suggestion generation.
    """
    
    def __init__(self):
        """
        Initialize the spell checker.
        """
        self.dictionary = set()
        self.word_frequencies = defaultdict(int)
    
    def load_dictionary(self, words: List[str]) -> None:
        """
        Load a dictionary of words into the spell checker.
        
        Args:
            words: List of valid words
        """
        for word in words:
            self.dictionary.add(word.lower())
    
    def add_word(self, word: str, frequency: int = 1) -> None:
        """
        Add a word to the dictionary with frequency information.
        
        Args:
            word: Word to add
            frequency: Frequency of the word
        """
        word = word.lower()
        self.dictionary.add(word)
        self.word_frequencies[word] += frequency
    
    def is_correct(self, word: str) -> bool:
        """
        Check if a word is spelled correctly.
        
        Args:
            word: Word to check
            
        Returns:
            True if word is in dictionary, False otherwise
        """
        return word.lower() in self.dictionary
    
    def _edit_distance(self, s1: str, s2: str) -> int:
        """
        Calculate edit distance between two strings using dynamic programming.
        
        Args:
            s1: First string
            s2: Second string
            
        Returns:
            Edit distance (number of operations needed to transform s1 to s2)
        """
        if len(s1) < len(s2):
            return self._edit_distance(s2, s1)
        
        if len(s2) == 0:
            return len(s1)
        
        previous_row = list(range(len(s2) + 1))
        
        for i, c1 in enumerate(s1):
            current_row = [i + 1]
            
            for j, c2 in enumerate(s2):
                # Cost of insertions, deletions, and substitutions
                insertions = previous_row[j + 1] + 1
                deletions = current_row[j] + 1
                substitutions = previous_row[j] + (c1 != c2)
                
                current_row.append(min(insertions, deletions, substitutions))
            
            previous_row = current_row
        
        return previous_row[-1]
    
    def get_suggestions(self, word: str, max_distance: int = 2, max_suggestions: int = 10) -> List[Tuple[str, int, float]]:
        """
        Get spelling suggestions for a misspelled word.
        
        Args:
            word: Misspelled word
            max_distance: Maximum edit distance for suggestions
            max_suggestions: Maximum number of suggestions to return
            
        Returns:
            List of (suggestion, edit_distance, frequency) tuples
        """
        word = word.lower()
        suggestions = []
        
        for dict_word in self.dictionary:
            distance = self._edit_distance(word, dict_word)
            
            if distance <= max_distance:
                frequency = self.word_frequencies.get(dict_word, 1)
                suggestions.append((dict_word, distance, frequency))
        
        # Sort by edit distance first, then by frequency
        suggestions.sort(key=lambda x: (x[1], -x[2]))
        
        return suggestions[:max_suggestions]
    
    def correct_text(self, text: str) -> str:
        """
        Correct spelling in a text.
        
        Args:
            text: Text to correct
            
        Returns:
            Corrected text
        """
        words = text.split()
        corrected_words = []
        
        for word in words:
            # Remove punctuation for checking
            clean_word = re.sub(r'[^a-zA-Z]', '', word)
            
            if clean_word and not self.is_correct(clean_word):
                # Get suggestions
                suggestions = self.get_suggestions(clean_word, max_distance=2, max_suggestions=1)
                
                if suggestions:
                    # Replace with best suggestion, preserving punctuation
                    corrected_word = word.replace(clean_word, suggestions[0][0])
                    corrected_words.append(corrected_word)
                else:
                    corrected_words.append(word)  # Keep original if no suggestions
            else:
                corrected_words.append(word)
        
        return ' '.join(corrected_words)


def demonstrate_word_frequency_analysis():
    """
    Demonstrate word frequency analysis.
    """
    print("=== Word Frequency Analysis Demonstration ===\n")
    
    # Sample text
    sample_text = """
    Python is a powerful programming language. Python is widely used in data science.
    Python has a simple syntax. Python is great for beginners. Python is also used
    in web development, machine learning, and artificial intelligence. Python's
    versatility makes it popular among developers. Python is open source and free.
    """
    
    analyzer = WordFrequencyAnalyzer()
    analyzer.add_text(sample_text)
    
    print("Sample text analyzed:")
    print(sample_text.strip())
    
    print("\nWord frequency analysis:")
    analyzer.display_statistics()
    
    # Test specific word lookups
    test_words = ["python", "programming", "language", "data", "machine", "artificial"]
    print(f"\nSpecific word frequencies:")
    for word in test_words:
        freq = analyzer.get_word_frequency(word)
        prob = analyzer.get_word_probability(word)
        print(f"  '{word}': {freq} occurrences ({prob:.3f} probability)")


def demonstrate_document_similarity():
    """
    Demonstrate document similarity using MinHash.
    """
    print("\n=== Document Similarity Demonstration ===\n")
    
    # Sample documents
    documents = {
        "doc1": "Python is a powerful programming language used in data science and machine learning.",
        "doc2": "Python programming language is widely used for data analysis and artificial intelligence.",
        "doc3": "Java is another popular programming language used in enterprise applications.",
        "doc4": "Machine learning and data science are important fields in computer science.",
        "doc5": "Python is great for beginners because it has simple syntax and readability."
    }
    
    similarity_analyzer = MinHashDocumentSimilarity(num_hashes=50)
    
    # Add documents
    for doc_id, text in documents.items():
        similarity_analyzer.add_document(doc_id, text)
        print(f"Added {doc_id}: {text}")
    
    print(f"\nDocument similarity analysis:")
    
    # Compare documents
    for doc1_id in documents:
        print(f"\nSimilar documents to {doc1_id}:")
        similar_docs = similarity_analyzer.find_similar_documents(doc1_id, threshold=0.1)
        
        for doc2_id, similarity in similar_docs:
            print(f"  {doc2_id}: {similarity:.3f} similarity")
            
            # Show actual vs estimated similarity
            actual_similarity = similarity_analyzer.jaccard_similarity(doc1_id, doc2_id)
            print(f"    Actual Jaccard similarity: {actual_similarity:.3f}")
            print(f"    MinHash estimate: {similarity:.3f}")
            print(f"    Difference: {abs(actual_similarity - similarity):.3f}")


def demonstrate_ngram_analysis():
    """
    Demonstrate N-gram analysis.
    """
    print("\n=== N-Gram Analysis Demonstration ===\n")
    
    # Sample text
    sample_text = """
    The quick brown fox jumps over the lazy dog. The quick brown fox is fast.
    The lazy dog sleeps all day. The quick brown fox runs through the forest.
    """
    
    # Test different n-gram sizes
    for n in [2, 3]:
        print(f"--- {n}-gram Analysis ---")
        
        ngram_analyzer = NGramAnalyzer(n=n)
        ngram_analyzer.add_text(sample_text)
        
        print(f"Top 10 {n}-grams:")
        top_ngrams = ngram_analyzer.get_top_ngrams(10)
        
        for i, (ngram, count) in enumerate(top_ngrams, 1):
            ngram_str = " ".join(ngram)
            print(f"  {i:2d}. '{ngram_str}' : {count}")
        
        # Test next word prediction
        if n >= 2:
            print(f"\nNext word prediction:")
            test_contexts = ["the quick", "brown fox", "lazy dog"]
            
            for context in test_contexts:
                predictions = ngram_analyzer.predict_next_word(context)
                print(f"  After '{context}':")
                
                for word, prob in predictions[:3]:  # Top 3 predictions
                    print(f"    {word} ({prob:.3f})")
        
        print()


def demonstrate_spell_checker():
    """
    Demonstrate spell checker functionality.
    """
    print("\n=== Spell Checker Demonstration ===\n")
    
    # Sample dictionary
    dictionary_words = [
        "python", "programming", "language", "computer", "science",
        "data", "analysis", "machine", "learning", "artificial",
        "intelligence", "algorithm", "function", "variable", "string",
        "integer", "boolean", "array", "list", "dictionary", "tuple",
        "class", "object", "method", "attribute", "inheritance",
        "polymorphism", "encapsulation", "abstraction", "recursion"
    ]
    
    spell_checker = SpellChecker()
    spell_checker.load_dictionary(dictionary_words)
    
    # Add some frequency information
    for word in ["python", "programming", "language", "computer"]:
        spell_checker.add_word(word, frequency=10)
    
    # Test spelling
    test_words = ["pythn", "programing", "langauge", "computr", "algoritm", "funtion"]
    
    print("Spelling check results:")
    for word in test_words:
        is_correct = spell_checker.is_correct(word)
        print(f"  '{word}': {'✓ Correct' if is_correct else '✗ Incorrect'}")
        
        if not is_correct:
            suggestions = spell_checker.get_suggestions(word, max_distance=2, max_suggestions=3)
            print(f"    Suggestions:")
            for suggestion, distance, freq in suggestions:
                print(f"      {suggestion} (distance: {distance}, freq: {freq})")
    
    # Test text correction
    print(f"\nText correction:")
    test_text = "Pythn is a great programing langauge for computr science."
    corrected_text = spell_checker.correct_text(test_text)
    
    print(f"Original: {test_text}")
    print(f"Corrected: {corrected_text}")


if __name__ == "__main__":
    """
    Main execution block. When this file is run directly, it will demonstrate:
    1. Word frequency analysis
    2. Document similarity using MinHash
    3. N-gram analysis
    4. Spell checking
    """
    
    # Run all demonstrations
    demonstrate_word_frequency_analysis()
    demonstrate_document_similarity()
    demonstrate_ngram_analysis()
    demonstrate_spell_checker()
    
    print("\n" + "="*70)
    print("EDUCATIONAL NOTES:")
    print("="*70)
    print("1. Word Frequency Analysis:")
    print("   - Hash tables provide O(1) average-case lookup for word counts")
    print("   - Essential for text analysis and language modeling")
    print("   - TF-IDF helps identify important words in documents")
    print()
    print("2. Document Similarity (MinHash):")
    print("   - Efficiently estimates Jaccard similarity between documents")
    print("   - Useful for plagiarism detection and document clustering")
    print("   - Trade-off between accuracy and computational efficiency")
    print()
    print("3. N-gram Analysis:")
    print("   - Captures local patterns in text")
    print("   - Useful for language modeling and text generation")
    print("   - Higher n captures more context but requires more data")
    print()
    print("4. Spell Checking:")
    print("   - Hash tables enable fast dictionary lookups")
    print("   - Edit distance helps find similar words")
    print("   - Frequency information improves suggestion quality")
    print()
    print("5. NLP Applications of Hashing:")
    print("   - Text preprocessing and tokenization")
    print("   - Vocabulary building and management")
    print("   - Efficient similarity computations")
    print("   - Pattern recognition and analysis")
    print("   - Real-time text processing systems")
