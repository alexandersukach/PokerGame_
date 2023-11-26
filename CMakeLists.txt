cmake_minimum_required(VERSION 3.26)

project(PokerGame_)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    game BettingRound.cpp Card.cpp Deck.cpp
    DoublyLinkedList.cpp Game.cpp Hand.cpp Player.cpp PokerGame.cpp)