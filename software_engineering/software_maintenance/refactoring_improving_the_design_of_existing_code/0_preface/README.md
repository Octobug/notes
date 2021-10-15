# Preface

## What is Refactoring?

Refactoring is the process of changing a software system in a way that does not
alter the external behavior of the code yet improves its internal structure. It
is a disciplined way to clean up code that minimizes the chances of introducing
bugs. In essence, when you refactor, you are improving the design of the code
after it has been written.

“Improving the design after it has been written.” That’s an odd turn of phrase.
For much of the history of software development, most people believed that we
design first, and only when done with design should we code. Over time, the
code will be modified, and the integrity of the system—its structure according
to that design—gradually fades. The code slowly sinks from engineering to
hacking.

Refactoring is the opposite of this practice. With refactoring, we can take a
bad, even chaotic, design and rework it into well-structured code. Each step is
simple—even simplistic. I move a field from one class to another, pull some
code out of a method to make it into its own method, or push some code up or
down a hierarchy. Yet the cumulative effect of these small changes can
radically improve the design. It is the exact reverse of the notion of software
decay.

With refactoring, the balance of work changes. I found that design, rather than
occurring all up front, occurs continuously during development. As I build the
system, I learn how to improve the design. The result of this interaction is a
program whose design stays good as development continues.

> progress: <https://memberservices.informit.com/my_account/webedition/9780135425664/html/preface.html>
