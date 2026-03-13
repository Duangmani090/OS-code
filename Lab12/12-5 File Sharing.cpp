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
int fd = open(filename, O_RDONLY);
if (fd == -1) { perror(&quot;open&quot;); return; }
// LOCK_SH: shared lock (multiple readers allowed simultaneously)
if (flock(fd, LOCK_SH) == -1) { perror(&quot;flock&quot;); close(fd); return; }
char buf[256]; ssize_t n;
cout &lt;&lt; &quot;Reader output:&quot; &lt;&lt; endl;
while ((n = read(fd, buf, sizeof(buf)-1)) &gt; 0) {
buf[n] = &#39;\0&#39;;
cout &lt;&lt; buf;
}
flock(fd, LOCK_UN); // Release shared lock
close(fd);
}
int main() {
writer(&quot;shared.txt&quot;, &quot;Process A data&quot;);
writer(&quot;shared.txt&quot;, &quot;Process B data&quot;);
reader(&quot;shared.txt&quot;);
return 0;
}
// LOCK_SH: multiple readers concurrently OK
// LOCK_EX: single writer; blocks all other readers and writers
