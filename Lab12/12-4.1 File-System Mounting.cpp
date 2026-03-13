#include &lt;iostream&gt;
#include &lt;fstream&gt;
#include &lt;sstream&gt;
#include &lt;iomanip&gt;
#include &lt;string&gt;
using namespace std;
struct MountEntry {
string device, mountPoint, fsType, options;
};
int main() {
ifstream mountFile(&quot;/proc/mounts&quot;); // Linux mount table
if (!mountFile.is_open()) {
cerr &lt;&lt; &quot;Cannot open /proc/mounts&quot; &lt;&lt; endl;
return 1;
}
cout &lt;&lt; left &lt;&lt; setw(20) &lt;&lt; &quot;DEVICE&quot;
&lt;&lt; setw(25) &lt;&lt; &quot;MOUNT POINT&quot;
&lt;&lt; setw(12) &lt;&lt; &quot;TYPE&quot;
&lt;&lt; &quot;OPTIONS&quot; &lt;&lt; endl;
cout &lt;&lt; string(75, &#39;=&#39;) &lt;&lt; endl;
string line;
while (getline(mountFile, line)) {
istringstream iss(line);
MountEntry e;
int dumpFreq, passNo;
iss &gt;&gt; e.device &gt;&gt; e.mountPoint &gt;&gt; e.fsType &gt;&gt; e.options
&gt;&gt; dumpFreq &gt;&gt; passNo;
cout &lt;&lt; left &lt;&lt; setw(20) &lt;&lt; e.device
&lt;&lt; setw(25) &lt;&lt; e.mountPoint
&lt;&lt; setw(12) &lt;&lt; e.fsType
&lt;&lt; e.options &lt;&lt; endl;
}
mountFile.close();
return 0;
}
