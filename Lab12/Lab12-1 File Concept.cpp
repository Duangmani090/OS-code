#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;string&gt;
using namespace std;

int main() {
// Create and write to file
ofstream outFile(&quot;data.txt&quot;);
if (!outFile.is_open()) {
cerr &lt;&lt; &quot;Error: Could not create data.txt&quot; &lt;&lt; endl;
return 1;
}
outFile &lt;&lt; &quot;Line 1: File Concept&quot; &lt;&lt; endl;
outFile &lt;&lt; &quot;Line 2: Access Methods&quot; &lt;&lt; endl;
outFile &lt;&lt; &quot;Line 3: Protection&quot; &lt;&lt; endl;
outFile.close();
// Read back from file
ifstream inFile(&quot;data.txt&quot;);
if (!inFile.is_open()) {
cerr &lt;&lt; &quot;Error: Could not open data.txt&quot; &lt;&lt; endl;
return 1;
}
string line;
cout &lt;&lt; &quot;File contents:&quot; &lt;&lt; endl;
while (getline(inFile, line)) {
cout &lt;&lt; line &lt;&lt; endl;
}
inFile.close();
return 0;
}
// Output:
// File contents:
// Line 1: File Concept
// Line 2: Access Methods
// Line 3: Protection
