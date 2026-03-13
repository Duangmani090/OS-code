#include &lt;iostream&gt;
#include &lt;fstream&gt;
using namespace std;
int main() {
// Sequential Write
ofstream out(&quot;records.bin&quot;, ios::binary);
int values[] = {100, 200, 300, 400, 500};
for (int i = 0; i &lt; 5; i++) {
out.write(reinterpret_cast&lt;char*&gt;(&amp;values[i]), sizeof(int));
}
out.close();
// Sequential Read
ifstream in(&quot;records.bin&quot;, ios::binary);
int val;
int pos = 0;
cout &lt;&lt; &quot;Sequential Read:&quot; &lt;&lt; endl;
while (in.read(reinterpret_cast&lt;char*&gt;(&amp;val), sizeof(int))) {
cout &lt;&lt; &quot;Record[&quot; &lt;&lt; pos++ &lt;&lt; &quot;] = &quot; &lt;&lt; val &lt;&lt; endl;
}
in.close();
return 0;
}
// Output:
// Sequential Read:
// Record[0] = 100
// Record[1] = 200
// Record[2] = 300
// Record[3] = 400
// Record[4] = 500
