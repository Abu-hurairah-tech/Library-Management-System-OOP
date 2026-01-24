CXX = g++
# Added -mconsole to force console mode
CXXFLAGS = -I./Books-Portal -I./Issue-Portal -I./Library-System -I./Login-Portal -I./Members-Portal -I./Utilities -std=c++11 -mconsole

SRCS = main.cpp \
       ./Books-Portal/Books-portal.cpp \
       ./Issue-Portal/Issue-portal.cpp \
       ./Library-System/Library.cpp \
       ./Library-System/Library-Books-Management.cpp \
       ./Library-System/Library-Member-Management.cpp \
       ./Login-Portal/login.cpp \
       ./Members-Portal/members.cpp \
       ./Utilities/DateUtils.cpp

main.exe: $(SRCS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o main.exe

clean:
	del main.exe