#include &lt;iostream&gt;
#include &lt;filesystem&gt;
namespace fs = std::filesystem;
void traverseDirectory(const fs::path&amp; dirPath, int depth = 0) {
std::string indent(depth * 2, &#39; &#39;);
try {
for (const auto&amp; entry : fs::directory_iterator(dirPath)) {
if (entry.is_directory()) {
cout &lt;&lt; indent &lt;&lt; &quot;[DIR] &quot; &lt;&lt; entry.path().filename().string()
&lt;&lt; &quot;/&quot; &lt;&lt; endl;
traverseDirectory(entry.path(), depth + 1); // Recurse
} else {
cout &lt;&lt; indent &lt;&lt; &quot;[FILE] &quot; &lt;&lt; entry.path().filename().string()
&lt;&lt; &quot; (&quot; &lt;&lt; entry.file_size() &lt;&lt; &quot; B)&quot; &lt;&lt; endl;
}
}
} catch (const fs::filesystem_error&amp; e) {
cout &lt;&lt; indent &lt;&lt; &quot; [Permission denied: &quot; &lt;&lt; e.what() &lt;&lt; &quot;]&quot; &lt;&lt; endl;
}
}
int main() {
traverseDirectory(&quot;.&quot;);
return 0;
}
// This mirrors the OS inode traversal used in hierarchical
// (tree-structured) directory systems described in OSC Ch.13
