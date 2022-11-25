all: cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4

cyoa-step1: cyoa-step1.cpp Page.cpp Tool.cpp
	g++ -o cyoa-step1 -pedantic -Wall -Werror -ggdb3 -std=gnu++98 cyoa-step1.cpp Page.cpp Tool.cpp

cyoa-step2: cyoa-step2.cpp Page.cpp Tool.cpp Game.cpp
	g++ -o cyoa-step2 -pedantic -Wall -Werror -ggdb3 -std=c++98 cyoa-step2.cpp Page.cpp Tool.cpp Game.cpp

cyoa-step3: cyoa-step3.cpp Page.cpp Tool.cpp Game.cpp
	g++ -o cyoa-step3 -pedantic -Wall -Werror -ggdb3 -std=c++98 cyoa-step3.cpp Page.cpp Tool.cpp Game.cpp

cyoa-step4: cyoa-step4.cpp Page.cpp Tool.cpp Game.cpp
	g++ -o cyoa-step4 -pedantic -Wall -Werror -ggdb3 -std=c++98 cyoa-step4.cpp Page.cpp Tool.cpp Game.cpp

clean:
	rm -f cyoa-step1 cyoa-step2 cyoa-step3 cyoa-step4


