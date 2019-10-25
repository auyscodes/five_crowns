cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(src
        Card.cpp
        Card.h
        CardCollection.h
        CardInterface.h
        CardPile.cpp
        CardPile.h
        Computer.cpp
        Computer.h
        DataLayer.cpp
        DataLayer.h
        Deck.cpp
        Deck.h
        DiscardPile.cpp
        DiscardPile.h
        DrawPile.cpp
        DrawPile.h
        Game.cpp
        Game.h
        Human.cpp
        Human.h
        ISave.cpp
        Joker.cpp
        Joker.h
        main.cpp
        Player.cpp
        Player.h
        Round.cpp
        Round.h
        Serialization.cpp
        Serialization.h)
