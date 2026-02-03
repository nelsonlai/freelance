/*
 * user_test.c - userspace test program for the ctut character device tutorial.
 *
 * Build:
 *   make user_test
 *
 * Run:
 *   ./user_test /dev/ctut0
 *
 * This demonstrates:
 *   - open()
 *   - write()
 *   - lseek()
 *   - read()
 *   - ioctl(CLEAR)
 */

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

/* Must match the driver’s ioctl definitions. */
#define CTUT_IOCTL_MAGIC  'c'
#define CTUT_IOCTL_CLEAR  _IO(CTUT_IOCTL_MAGIC, 0x01)

/* kfifo version uses a different magic; we try both for convenience. */
#define CTUT_FIFO_IOCTL_MAGIC  'f'
#define CTUT_FIFO_IOCTL_CLEAR  _IO(CTUT_FIFO_IOCTL_MAGIC, 0x01)

static void die(const char *msg)
{
	perror(msg);
	exit(1);
}

static void set_nonblock(int fd, int enable)
{
	int flags = fcntl(fd, F_GETFL);
	if (flags < 0)
		die("fcntl(F_GETFL)");

	if (enable)
		flags |= O_NONBLOCK;
	else
		flags &= ~O_NONBLOCK;

	if (fcntl(fd, F_SETFL, flags) < 0)
		die("fcntl(F_SETFL)");
}

int main(int argc, char **argv)
{
	const char *path = "/dev/ctut0";
	int fd;
	ssize_t n;
	char buf[128];

	if (argc >= 2)
		path = argv[1];

	fd = open(path, O_RDWR);
	if (fd < 0)
		die("open");

	printf("Opened %s\n", path);

	/* Write some data */
	{
		const char *msg = "hello from userspace\n";
		n = write(fd, msg, strlen(msg));
		if (n < 0)
			die("write");
		printf("Wrote %zd bytes\n", n);
	}

	/*
	 * Seek back to start (only works for the “file-like” ctut_char device).
	 *
	 * For the kfifo stream device (ctut_kfifo), lseek returns -ESPIPE.
	 * That’s expected: stream devices generally don’t support seeking.
	 */
	if (lseek(fd, 0, SEEK_SET) < 0) {
		if (errno == ESPIPE) {
			printf("Device is non-seekable (ESPIPE). Continuing as stream...\n");
		} else {
			die("lseek");
		}
	}

	/* Read it back */
	memset(buf, 0, sizeof(buf));
	n = read(fd, buf, sizeof(buf) - 1);
	if (n < 0)
		die("read");
	printf("Read %zd bytes: %s", n, buf);

	/* Clear device buffer via ioctl */
	if (ioctl(fd, CTUT_IOCTL_CLEAR) < 0) {
		/*
		 * If we’re talking to the kfifo version, the ioctl number differs.
		 * Try the FIFO clear as a fallback.
		 */
		if (ioctl(fd, CTUT_FIFO_IOCTL_CLEAR) < 0)
			die("ioctl(CLEAR)");
	}
	printf("Cleared device buffer via ioctl\n");

	/*
	 * Verify “empty” after clearing:
	 *
	 * - For ctut_char (file-like buffer), read returns 0 (EOF) at end.
	 * - For ctut_kfifo (stream FIFO), a blocking read would SLEEP forever
	 *   on an empty FIFO. So we force O_NONBLOCK and expect -EAGAIN.
	 */
	set_nonblock(fd, 1);
	n = read(fd, buf, sizeof(buf) - 1);
	if (n < 0) {
		if (errno == EAGAIN)
			printf("After clear, non-blocking read returned EAGAIN (expected for FIFO)\n");
		else
			die("read(after clear)");
	} else {
		printf("After clear, read returned %zd bytes\n", n);
	}
	set_nonblock(fd, 0);

	close(fd);
	return 0;
}

