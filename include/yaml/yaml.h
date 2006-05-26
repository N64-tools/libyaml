/**
 * @file yaml.h
 * @brief Public interface for libyaml.
 * 
 * Include the header file with the code:
 * @code
 * #include <yaml/yaml.h>
 * @endcode
 */

#ifndef YAML_H
#define YAML_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/**
 * @defgroup version Version Information
 * @{
 */

/**
 * Get the library version as a string.
 *
 * @returns The function returns the pointer to a static string of the form
 * @c "X.Y.Z", where @c X is the major version number, @c Y is a minor version
 * number, and @c Z is the patch version number.
 */

const char *
yaml_get_version_string(void);

/**
 * Get the library version numbers.
 *
 * @param[out]  major   Major version number.
 * @param[out]  minor   Minor version number.
 * @param[out]  patch   Patch version number.
 */

void
yaml_get_version(int *major, int *minor, int *patch);

/** @} */

/**
 * @defgroup basic Basic Types
 * @{
 */

/** The character type. */
typedef unsigned char yaml_char_t;

/** The stream encoding. */
typedef enum {
    YAML_ANY_ENCODING,
    YAML_UTF8_ENCODING,
    YAML_UTF16LE_ENCODING,
    YAML_UTF16BE_ENCODING
} yaml_encoding_t;

/** @} */

/*

typedef enum {
    YAML_NO_ERROR,

    YAML_MEMORY_ERROR,

    YAML_READER_ERROR,
    YAML_SCANNER_ERROR,
    YAML_PARSER_ERROR,

    YAML_WRITER_ERROR,
    YAML_EMITTER_ERROR
} yaml_error_type_t;

typedef enum {
    YAML_ANY_SCALAR_STYLE,
    YAML_PLAIN_SCALAR_STYLE,
    YAML_SINGLE_QUOTED_SCALAR_STYLE,
    YAML_DOUBLE_QUOTED_SCALAR_STYLE,
    YAML_LITERAL_SCALAR_STYLE,
    YAML_FOLDED_SCALAR_STYLE
} yaml_scalar_style_t;

typedef enum {
    YAML_ANY_SEQUENCE_STYLE,
    YAML_BLOCK_SEQUENCE_STYLE,
    YAML_FLOW_SEQUENCE_STYLE
} yaml_sequence_style_t;

typedef enum {
    YAML_ANY_MAPPING_STYLE,
    YAML_BLOCK_MAPPING_STYLE,
    YAML_FLOW_MAPPING_STYLE
} yaml_mapping_style_t;

typedef enum {
    YAML_STREAM_START_TOKEN,
    YAML_STREAM_END_TOKEN,

    YAML_VERSION_DIRECTIVE_TOKEN,
    YAML_TAG_DIRECTIVE_TOKEN,
    YAML_DOCUMENT_START_TOKEN,
    YAML_DOCUMENT_END_TOKEN,

    YAML_BLOCK_SEQUENCE_START_TOKEN,
    YAML_BLOCK_MAPPING_START_TOKEN,
    YAML_BLOCK_END_TOKEN,

    YAML_FLOW_SEQUENCE_START_TOKEN,
    YAML_FLOW_SEQUENCE_END_TOKEN,
    YAML_FLOW_MAPPING_START_TOKEN,
    YAML_FLOW_MAPPING_END_TOKEN,

    YAML_BLOCK_ENTRY_TOKEN,
    YAML_FLOW_ENTRY_TOKEN,
    YAML_KEY_TOKEN,
    YAML_VALUE_TOKEN,

    YAML_ALIAS_TOKEN,
    YAML_ANCHOR_TOKEN,
    YAML_TAG_TOKEN,
    YAML_SCALAR_TOKEN
} yaml_token_type_t;

typedef enum {
    YAML_STREAM_START_EVENT,
    YAML_STREAM_END_EVENT,

    YAML_DOCUMENT_START_EVENT,
    YAML_DOCUMENT_END_EVENT,

    YAML_ALIAS_EVENT,
    YAML_SCALAR_EVENT,

    YAML_SEQUENCE_START_EVENT,
    YAML_SEQUENCE_END_EVENT,

    YAML_MAPPING_START_EVENT,
    YAML_MAPPING_END_EVENT
} yaml_event_type_t;

typedef struct {
    size_t offset;
    size_t index;
    size_t line;
    size_t column;
} yaml_mark_t;

typedef struct {
    yaml_error_type_t type;
    char *context;
    yaml_mark_t context_mark;
    char *problem;
    yaml_mark_t problem_mark;
} yaml_error_t;

typedef struct {
    yaml_token_type_t type;
    union {
        yaml_encoding_t encoding;
        char *anchor;
        char *tag;
        struct {
            char *value;
            size_t length;
            yaml_scalar_style_t style;
        } scalar;
        struct {
            int major;
            int minor;
        } version;
        struct {
          char *handle;
          char *prefix;
        } tag_pair;
    } data;
    yaml_mark_t start_mark;
    yaml_mark_t end_mark;
} yaml_token_t;

typedef struct {
    yaml_event_type_t type;
    union {
        struct {
            yaml_encoding_t encoding;
        } stream_start;
        struct {
            struct {
                int major;
                int minor;
            } version;
            struct {
                char *handle;
                char *prefix;
            } **tag_pairs;
            int implicit;
        } document_start;
        struct {
            int implicit;
        } document_end;
        struct {
            char *anchor;
        } alias;
        struct {
            char *anchor;
            char *tag;
            char *value;
            size_t length;
            int plain_implicit;
            int quoted_implicit;
            yaml_scalar_style_t style;
        } scalar;
        struct {
            char *anchor;
            char *tag;
            int implicit;
            yaml_sequence_style_t style;
        } sequence_start;
        struct {
            char *anchor;
            char *tag;
            int implicit;
            yaml_mapping_style_t style;
        } mapping_start;
    } data;
    yaml_mark_t start_mark;
    yaml_mark_t end_mark;
} yaml_event_t;

*/


/**
 * @defgroup parser Parser Definitions
 * @{
 */

/**
 * The prototype of a read handler.
 *
 * The read handler is called when the parser needs to read more bytes from the
 * source.  The handler should write not more than @a size bytes to the @a
 * buffer.  The number of written bytes should be set to the @a length variable.
 *
 * @param[in]   ext     A pointer to an application data specified by
 *                      @c yaml_parser_set_read_handler.
 * @param[out]  buffer  The buffer to write the data from the source.
 * @param[in]   size    The size of the buffer.
 * @param[out]  length  The actual number of bytes read from the source.
 *
 * @returns On success, the handler should return @c 1.  If the handler failed,
 * the returned value should be @c 0.  On EOF, the handler should set the
 * @a length to @c 0 and return @c 1.
 */
typedef int yaml_read_handler_t(void *ext, yaml_char_t *buffer, size_t size,
        size_t *length);


/**
 * The parser structure.
 *
 * All members are internal.  Manage the structure using the @c yaml_parser_
 * family of functions.
 */

typedef struct {

    /**
     * @name Reader stuff
     * @{
     */

    /** Read handler */
    yaml_read_handler_t *reader;

    /** A pointer for passing to the read handler. */
    void *reader_ext;

    /** EOF flag */
    int eof;

    /** The pointer to the beginning of the working buffer. */
    yaml_char_t *buffer;

    /** The pointer to the current character in the working buffer. */
    yaml_char_t *pointer;

    /** The remaining undecoded characters. */
    unsigned char *raw_buffer;

    /** The size of the raw buffer. */
    size_t raw_buffer_size;

    /** The input encoding. */
    yaml_encoding_t encoding;

    /**
     * @}
     */

} yaml_parser_t;

/**
 * Create a new parser.
 *
 * This function creates a new parser object.  An application is responsible
 * for destroying the object using the @c yaml_parser_delete function.
 *
 * @returns A new parser object; @c NULL on error.
 */

yaml_parser_t *
yaml_parser_new(void);

/**
 * Destroy a parser.
 *
 * @param[in]   parser  A parser object.
 */

void
yaml_parser_delete(yaml_parser_t *parser);

/** @} */

/*
typedef struct {
} yaml_emitter_t;
*/

#ifdef __cplusplus
}
#endif

#endif /* #ifndef YAML_H */
