#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;unistd.h&gt; // link(), symlink(), unlink()
#include &lt;sys/stat.h&gt;
using namespace std;
int main() {

// Create original file
ofstream f(&quot;original.txt&quot;);
f &lt;&lt; &quot;File sharing via links!&quot;;
f.close();
// Hard link: same inode, different directory entry
link(&quot;original.txt&quot;, &quot;hardlink.txt&quot;);
// Symbolic link: separate inode pointing to path string
symlink(&quot;original.txt&quot;, &quot;symlink.txt&quot;);
// Check inode numbers
struct stat s1, s2, s3;
stat(&quot;original.txt&quot;, &amp;s1);
stat(&quot;hardlink.txt&quot;, &amp;s2);
lstat(&quot;symlink.txt&quot;, &amp;s3);
cout &lt;&lt; &quot;Original inode: &quot; &lt;&lt; s1.st_ino &lt;&lt; endl;
cout &lt;&lt; &quot;Hard link inode: &quot; &lt;&lt; s2.st_ino
&lt;&lt; &quot; (same? &quot; &lt;&lt; (s1.st_ino == s2.st_ino ? &quot;YES&quot; : &quot;NO&quot;) &lt;&lt; &quot;)&quot; &lt;&lt; endl;
cout &lt;&lt; &quot;Symlink inode: &quot; &lt;&lt; s3.st_ino
&lt;&lt; &quot; (same? &quot; &lt;&lt; (s1.st_ino == s3.st_ino ? &quot;YES&quot; : &quot;NO&quot;) &lt;&lt; &quot;)&quot; &lt;&lt; endl;
// Delete original
unlink(&quot;original.txt&quot;);
// Hard link still works (reference count &gt; 0)
ifstream h(&quot;hardlink.txt&quot;);
cout &lt;&lt; &quot;\nHard link after delete: &quot; &lt;&lt; (h.good() ? &quot;ACCESSIBLE&quot; : &quot;BROKEN&quot;)
&lt;&lt; endl;
// Symbolic link is now dangling
ifstream sym(&quot;symlink.txt&quot;);
cout &lt;&lt; &quot;Symbolic link after delete: &quot; &lt;&lt; (sym.good() ? &quot;ACCESSIBLE&quot; :
&quot;DANGLING/BROKEN&quot;) &lt;&lt; endl;
return 0;
}
// Hard link: file data survives until ALL hard links deleted (link count = 0)
// Symbolic link: dangling reference once target is removed
