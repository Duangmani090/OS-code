#include &lt;iostream&gt;
#include &lt;sys/stat.h&gt;

#include &lt;ctime&gt;
using namespace std;
int main() {
struct stat fileInfo;
const char* filename = &quot;data.txt&quot;;
if (stat(filename, &amp;fileInfo) != 0) {
cerr &lt;&lt; &quot;Error: Cannot retrieve file attributes&quot; &lt;&lt; endl;
return 1;
}
// st_size: file size in bytes
cout &lt;&lt; &quot;File: &quot; &lt;&lt; filename &lt;&lt; endl;
cout &lt;&lt; &quot;Size: &quot; &lt;&lt; fileInfo.st_size &lt;&lt; &quot; bytes&quot; &lt;&lt; endl;
// st_mtime: last modification time (Unix timestamp)
cout &lt;&lt; &quot;Last modified: &quot; &lt;&lt; ctime(&amp;fileInfo.st_mtime);
// st_mode: file type and permissions bitmask
cout &lt;&lt; &quot;Is regular file: &quot;
&lt;&lt; (S_ISREG(fileInfo.st_mode) ? &quot;Yes&quot; : &quot;No&quot;) &lt;&lt; endl;
return 0;
}
// Key attributes: st_size (size), st_mtime (modification time),
// st_mode (type/permissions), st_uid (owner), st_nlink (link count)
