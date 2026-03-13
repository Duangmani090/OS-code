#include &lt;iostream&gt;
#include &lt;sys/mount.h&gt;
#include &lt;cerrno&gt;
#include &lt;cstring&gt;
using namespace std;
int main() {
// mount(source, target, filesystemtype, mountflags, data)
// source : device or filesystem to mount (e.g., &quot;/dev/sdb1&quot;)
// target : mount point directory (must exist)
// fstype : filesystem type string (e.g., &quot;ext4&quot;, &quot;vfat&quot;)
// mountflags : bitmask options (MS_RDONLY, MS_NOEXEC, etc.)
// data : filesystem-specific options string
const char* source = &quot;/dev/sdb1&quot;; // Block device to mount
const char* target = &quot;/mnt/usb&quot;; // Existing mount point
const char* fstype = &quot;vfat&quot;; // Filesystem type
unsigned long flags = MS_RDONLY; // Read-only mount
const char* options = &quot;utf8&quot;; // FS-specific options
cout &lt;&lt; &quot;Attempting to mount &quot; &lt;&lt; source
&lt;&lt; &quot; at &quot; &lt;&lt; target &lt;&lt; &quot;...&quot; &lt;&lt; endl;
// Note: requires root privileges (CAP_SYS_ADMIN)
if (mount(source, target, fstype, flags, options) == -1) {
cerr &lt;&lt; &quot;mount() failed: &quot; &lt;&lt; strerror(errno) &lt;&lt; endl;
cerr &lt;&lt; &quot;(This is expected without root and real device)&quot; &lt;&lt; endl;
return 1;
}
cout &lt;&lt; &quot;Mount successful!&quot; &lt;&lt; endl;
// To unmount: umount(target) or umount2(target, MNT_FORCE)
return 0;
}
// Key flags: MS_RDONLY (read-only), MS_NOEXEC (no execution),
// MS_NOSUID (ignore SUID bits), MS_REMOUNT (remount with new flags)
