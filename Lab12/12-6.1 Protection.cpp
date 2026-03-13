#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;unistd.h&gt; // access()
#include &lt;sys/stat.h&gt;
#include &lt;cerrno&gt;
#include &lt;cstring&gt;
using namespace std;
void checkPermissions(const char* path) {
cout &lt;&lt; &quot;Checking permissions for: &quot; &lt;&lt; path &lt;&lt; endl;
// access() checks real UID/GID permissions
cout &lt;&lt; &quot; Read (R_OK): &quot;
&lt;&lt; (access(path, R_OK) == 0 ? &quot;ALLOWED&quot; : &quot;DENIED&quot;) &lt;&lt; endl;
cout &lt;&lt; &quot; Write (W_OK): &quot;
&lt;&lt; (access(path, W_OK) == 0 ? &quot;ALLOWED&quot; : &quot;DENIED&quot;) &lt;&lt; endl;
cout &lt;&lt; &quot; Execute (X_OK): &quot;
&lt;&lt; (access(path, X_OK) == 0 ? &quot;ALLOWED&quot; : &quot;DENIED&quot;) &lt;&lt; endl;
cout &lt;&lt; &quot; Exists (F_OK): &quot;
&lt;&lt; (access(path, F_OK) == 0 ? &quot;YES&quot; : &quot;NO&quot;) &lt;&lt; endl;
}
void safeOpen(const char* path) {
if (access(path, R_OK) != 0) {
cerr &lt;&lt; &quot;Permission denied: cannot read &#39;&quot; &lt;&lt; path &lt;&lt; &quot;&#39;&quot; &lt;&lt; endl;
cerr &lt;&lt; &quot;Reason: &quot; &lt;&lt; strerror(errno) &lt;&lt; endl;

return;
}
ifstream f(path);
cout &lt;&lt; &quot;File opened successfully.&quot; &lt;&lt; endl;
}
int main() {
// Create test file with write-only permissions
ofstream f(&quot;test_perms.txt&quot;);
f &lt;&lt; &quot;test content&quot;;
f.close();
chmod(&quot;test_perms.txt&quot;, S_IWUSR); // write-only: no read
checkPermissions(&quot;test_perms.txt&quot;);
cout &lt;&lt; endl;
safeOpen(&quot;test_perms.txt&quot;); // Should be denied
chmod(&quot;test_perms.txt&quot;, S_IRUSR | S_IWUSR); // restore
return 0;
}
// access() vs open(): access() checks permissions WITHOUT opening;
// useful for pre-checks (though TOCTOU race conditions can occur)
