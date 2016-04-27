cmake_minimum_required(VERSION 3.4)
project(Server)

set(SOURCE_FILES_SERVER mq.h server.c server.h msg_linked_list.c msg_linked_list.h)
add_executable(Server ${SOURCE_FILES_SERVER})

project(Client)

set(SOURCE_FILES_CLIENT mq.h client.c client.h)
add_executable(Client ${SOURCE_FILES_CLIENT})


project(ListTest)

set(SOURCE_FILES_LIST_TEST msg_linked_list.c msg_linked_list.h list_test.c)
add_executable(ListTest ${SOURCE_FILES_LIST_TEST})