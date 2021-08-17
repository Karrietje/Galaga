My engine can run in x86 and x64 release/debug build. 
I use IMGUI for the buttons. For the fonts I'm using the Resourcemanager. 

**COMPONENTS OVER INHERITANCE** 
=> This means I tried to avoid in every way to use inheritance so I used a lot of components(see project).
I prefer to get the component I want to talk to from the GameObject. This is a simple and fast solution and it
is tightly coupled! Your composed class can be easily added without repercussions. It also allows us to delay the creation
of components until they are needed. So during programming, when you need something added to your character (like some kind of weapon), compositions
make it easier to adjust it. They can also be dynamically be changed! 
Components are best explained when using unity. In my project I made a class "Components" and "GameComponents"
where I add every component that I have to use during the programming phase. I can change them whenever I want during the process. 

**Gameloop and Update method**
In Scene.cpp I use a late update function (Update method). This to avoid that gameobject A won't get deleted if B still needs 
object A afterwards. This can result in errors, because B can't use A if A is already deleted! In the late update we do the cleanup. 

The gameloop is present in the project. 

**Commands**
I made a class "GameCommands" with the commands I'm using in my projects. This was made so I can use it for the move commands for
my QBert and for my controller support(input). Using commands is very beneficial because it's an object-oriented language. It's an easy way
to interact with every gameobject. 

**Observer/Eventqueue**
An observer is one of the design patters. It allows some objects to notify other objects(observers) about changes in their states. 
When one object changes state, all of its dependents are notified and also updated. 
A nice example in my project: I have an health and a point observer. These classes have a Notify function with an Event as parameter.
We have an Event called "kill". With the Healthobserver we let others know when the character loses HP or reaches zero. For the points we also
use the notify function that keeps the score during the whole game. 

Github link: https://github.com/Karrietje/Programming_Engine




