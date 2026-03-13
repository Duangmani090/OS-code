#include &lt;iostream&gt;
#include &lt;filesystem&gt;
namespace fs = std::filesystem;
int main() {
fs::path dirPath = &quot;.&quot;; // Current directory
cout &lt;&lt; &quot;Directory listing for: &quot; &lt;&lt; fs::absolute(dirPath) &lt;&lt; endl;
cout &lt;&lt; string(50, &#39;-&#39;) &lt;&lt; endl;
for (const auto&amp; entry : fs::directory_iterator(dirPath)) {
if (entry.is_regular_file()) {
cout &lt;&lt; &quot;[FILE] &quot; &lt;&lt; entry.path().filename().string()
&lt;&lt; &quot; (&quot; &lt;&lt; entry.file_size() &lt;&lt; &quot; bytes)&quot; &lt;&lt; endl;
} else if (entry.is_directory()) {
cout &lt;&lt; &quot;[DIR] &quot; &lt;&lt; entry.path().filename().string() &lt;&lt; &quot;/&quot; &lt;&lt; endl;
} else {
cout &lt;&lt; &quot;[OTHER] &quot; &lt;&lt; entry.path().filename().string() &lt;&lt; endl;
}
}
return 0;
}
// Compile: g++ -std=c++17 -o dir_list dir_list.cpp
// Concepts: directory_iterator traverses one level; use
// recursive_directory_iterator for full tree traversal
