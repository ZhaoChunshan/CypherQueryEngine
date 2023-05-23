# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (CypherQueryEngine)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
		PParser/Cypher/CypherBaseListener.cpp
		PParser/Cypher/CypherBaseVisitor.cpp
		PParser/Cypher/CypherLexer.cpp
		PParser/Cypher/CypherListener.cpp
		PParser/Cypher/CypherParser.cpp
		PParser/Cypher/CypherVisitor.cpp
		Value/Value.cpp
		Value/Expression.cpp
		Value/PCalculator.cpp
		PParser/Pattern.cpp
		PParser/CypherAST.cpp
		PParser/PCypherParser.cpp
		PQuery/PQueryOperator.cpp
		PQuery/PQueryTree.cpp
#		PQuery/PTempResult.cpp
		test.cpp

        )
# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${PROJECT_SOURCE_DIR}/PParser/Cypher"
        "${PROJECT_SOURCE_DIR}/PParser"
        "${PROJECT_SOURCE_DIR}/PQuery"
		"${PROJECT_SOURCE_DIR}/Value"
        "${PROJECT_SOURCE_DIR}/Tools/antlr4-cpp-runtime-4/runtime/src"
)
target_link_libraries( ${PROJECT_NAME}
    PRIVATE 
    "${PROJECT_SOURCE_DIR}/Tools/libantlr4-runtime.a"
)
