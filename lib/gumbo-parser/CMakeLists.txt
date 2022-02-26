set(GUMBO_SOURCES
        src/attribute.h
        src/attribute.c
        src/char_ref.h
        src/char_ref.c
        src/error.h
        src/error.c
        src/gumbo.h
        src/insertion_mode.h
        src/parser.h
        src/parser.c
        src/string_buffer.h
        src/string_buffer.c
        src/string_piece.h
        src/string_piece.c
        src/tag_enum.h
        src/tag_gperf.h
        src/tag_sizes.h
        src/tag_strings.h
        src/tag.c
        src/token_type.h
        src/tokenizer.h
        src/tokenizer.c
        src/tokenizer_states.h
        src/utf8.h
        src/utf8.c
        src/util.h
        src/util.c
        src/vector.h
        src/vector.c)

if (MSVC)
    include_directories(visualc/include)
    set(GUMBO_SOURCES ${GUMBO_SOURCES} visualc/include/strings.h)
endif()

add_library(gumbo STATIC ${GUMBO_SOURCES})
include_directories(src)

cmake_minimum_required(VERSION 3.20)