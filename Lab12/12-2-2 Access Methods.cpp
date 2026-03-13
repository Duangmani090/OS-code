#include &lt;iostream&gt;
#include &lt;fstream&gt;
using namespace std;
struct Record { int id; char name[20]; double value; };
int main() {
// Write 5 records
fstream file(&quot;direct.bin&quot;, ios::binary | ios::out | ios::in | ios::trunc);
Record records[] = {
{1,&quot;Alpha&quot;,1.1}, {2,&quot;Beta&quot;,2.2}, {3,&quot;Gamma&quot;,3.3},
{4,&quot;Delta&quot;,4.4}, {5,&quot;Epsilon&quot;,5.5}
};
for (auto&amp; r : records)
file.write(reinterpret_cast&lt;char*&gt;(&amp;r), sizeof(Record));
// Direct access: jump to record index 2 (3rd record)
int targetIndex = 2;
streampos offset = targetIndex * sizeof(Record);
file.seekp(offset, ios::beg); // seekp for write position
Record updated = {3, &quot;Gamma_UPDATED&quot;, 99.9};
file.write(reinterpret_cast&lt;char*&gt;(&amp;updated), sizeof(Record));
// Verify by reading all records
file.seekg(0, ios::beg);
Record r;
while (file.read(reinterpret_cast&lt;char*&gt;(&amp;r), sizeof(Record)))
cout &lt;&lt; &quot;ID:&quot; &lt;&lt; r.id &lt;&lt; &quot; Name:&quot; &lt;&lt; r.name &lt;&lt; &quot; Val:&quot; &lt;&lt; r.value &lt;&lt;
endl;
file.close();
return 0;
}
