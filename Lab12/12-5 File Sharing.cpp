#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;sys/file.h&gt; // flock()
#include &lt;fcntl.h&gt;
#include &lt;unistd.h&gt;
#include &lt;cstring&gt;
using namespace std;
// (a) WRITER: exclusive lock
void writer(const char* filename, const char* data) {
int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
if (fd == -1) { perror(&quot;open&quot;); return; }
// LOCK_EX: exclusive lock (blocks until available)
if (flock(fd, LOCK_EX) == -1) { perror(&quot;flock&quot;); close(fd); return; }
write(fd, data, strlen(data)); // Write data while holding lock
write(fd, &quot;\n&quot;, 1);
flock(fd, LOCK_UN); // Release exclusive lock
close(fd);
cout &lt;&lt; &quot;Writer: wrote and released lock&quot; &lt;&lt; endl;
}
// (b) READER: shared lock
void reader(const char* filename) {
