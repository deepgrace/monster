//
// Copyright (c) 2016-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/monster
//

#ifndef MONSTER_VERSION_HPP
#define MONSTER_VERSION_HPP

#define MONSTER_STRINGIZE(T) #T

/*
 *   MONSTER_VERSION_NUMBER
 *
 *   Identifies the API version of Monster.
 *   This is a simple integer that is incremented by one every
 *   time a set of code changes is merged to the master branch.
 */

#define MONSTER_VERSION_NUMBER 310
#define MONSTER_VERSION_STRING "Monster/" MONSTER_STRINGIZE(MONSTER_VERSION_NUMBER)

#endif
