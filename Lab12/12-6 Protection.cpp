#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;sys/stat.h&gt;
#include &lt;sys/types.h&gt;
using namespace std;
string permString(mode_t mode) {
string perm = &quot;---------&quot;;
// Owner
if (mode &amp; S_IRUSR) perm[0] = &#39;r&#39;;
if (mode &amp; S_IWUSR) perm[1] = &#39;w&#39;;
if (mode &amp; S_IXUSR) perm[2] = &#39;x&#39;;
// Group
if (mode &amp; S_IRGRP) perm[3] = &#39;r&#39;;
if (mode &amp; S_IWGRP) perm[4] = &#39;w&#39;;
if (mode &amp; S_IXGRP) perm[5] = &#39;x&#39;;
// Others
if (mode &amp; S_IROTH) perm[6] = &#39;r&#39;;
if (mode &amp; S_IWOTH) perm[7] = &#39;w&#39;;
if (mode &amp; S_IXOTH) perm[8] = &#39;x&#39;;
return perm;
}
int main() {
const char* fname = &quot;protected.txt&quot;;
// (a) Create file
ofstream f(fname);
f &lt;&lt; &quot;Sensitive data&quot;;
f.close();
// (b) Set permissions: 0600 = rw------- (owner read+write only)
if (chmod(fname, S_IRUSR | S_IWUSR) == -1) {
perror(&quot;chmod&quot;); return 1;
}
// (c) Read and display permissions
struct stat info;
stat(fname, &amp;info);

cout &lt;&lt; &quot;Permissions for &#39;&quot; &lt;&lt; fname &lt;&lt; &quot;&#39;: &quot;
&lt;&lt; permString(info.st_mode &amp; 0777) &lt;&lt; endl;
cout &lt;&lt; &quot;Octal: &quot; &lt;&lt; oct &lt;&lt; (info.st_mode &amp; 0777) &lt;&lt; dec &lt;&lt; endl;
// Output: Permissions: rw------- Octal: 600
return 0;
}
