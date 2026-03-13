#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;filesystem&gt;
#include &lt;sys/stat.h&gt;
#include &lt;iomanip&gt;
using namespace std;
namespace fs = std::filesystem;
string getPerms(fs::perms p) {
auto check = [&amp;](fs::perms bit, char c) {
return (p &amp; bit) != fs::perms::none ? c : &#39;-&#39;;
};
string s;
s += check(fs::perms::owner_read, &#39;r&#39;);
s += check(fs::perms::owner_write, &#39;w&#39;);
s += check(fs::perms::owner_exec, &#39;x&#39;);
s += check(fs::perms::group_read, &#39;r&#39;);
s += check(fs::perms::group_write, &#39;w&#39;);
s += check(fs::perms::group_exec, &#39;x&#39;);
s += check(fs::perms::others_read, &#39;r&#39;);
s += check(fs::perms::others_write,&#39;w&#39;);
s += check(fs::perms::others_exec, &#39;x&#39;);
return s;
}
// (a) List directory
void listDir(const string&amp; path) {
cout &lt;&lt; left &lt;&lt; setw(12) &lt;&lt; &quot;PERM&quot; &lt;&lt; setw(10) &lt;&lt; &quot;SIZE(B)&quot;
&lt;&lt; &quot;NAME&quot; &lt;&lt; endl &lt;&lt; string(40, &#39;-&#39;) &lt;&lt; endl;
for (auto&amp; e : fs::directory_iterator(path)) {
auto st = e.status();
uintmax_t sz = e.is_regular_file() ? e.file_size() : 0;
cout &lt;&lt; setw(12) &lt;&lt; getPerms(st.permissions())
&lt;&lt; setw(10) &lt;&lt; sz
&lt;&lt; e.path().filename().string() &lt;&lt; endl;
}
}
// (b) Copy file with enforcement
void copyFile(const string&amp; src, const string&amp; dst) {
struct stat info;
stat(src.c_str(), &amp;info);
// (c) Enforce read-only check
if (!(info.st_mode &amp; S_IRUSR)) {
cerr &lt;&lt; &quot;Error: No read permission on source.&quot; &lt;&lt; endl;
return;
}
try {
fs::copy_file(src, dst, fs::copy_options::overwrite_existing);
cout &lt;&lt; &quot;Copied: &quot; &lt;&lt; src &lt;&lt; &quot; -&gt; &quot; &lt;&lt; dst &lt;&lt; endl;
} catch (const fs::filesystem_error&amp; e) {
cerr &lt;&lt; &quot;Copy failed: &quot; &lt;&lt; e.what() &lt;&lt; endl;

}
}
int main() {
// Create demo files
ofstream(&quot;file_a.txt&quot;) &lt;&lt; &quot;Hello World&quot;;
ofstream(&quot;file_b.txt&quot;) &lt;&lt; &quot;OSC Chapter 13&quot;;
chmod(&quot;file_b.txt&quot;, 0444); // Make read-only
cout &lt;&lt; &quot;=== Directory Listing ===&quot; &lt;&lt; endl;
listDir(&quot;.&quot;);
cout &lt;&lt; endl;
copyFile(&quot;file_a.txt&quot;, &quot;file_a_copy.txt&quot;);
copyFile(&quot;file_b.txt&quot;, &quot;file_b_copy.txt&quot;);
return 0;
}
