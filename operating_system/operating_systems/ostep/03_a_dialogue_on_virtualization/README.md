# 3. A Dialogue on Virtualization

Assume there is one physical CPU in a system. What virtualization does is take
that single CPU and make it look like many virtual CPUs to the applications
running on the system. Thus, while each application thinks it has its own CPU
to use, there is really only one. And thus the OS has created a beautiful
illusion: it has virtualized the CPU.
