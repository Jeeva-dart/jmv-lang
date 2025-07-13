typedef enum {
    INT,
} TypeLiteral;

typedef enum  {
    EXIT,
} TypeKeyword;

typedef enum {
    SEMI,
    OPEN_PAREN,
    CLOSE_PAREN
} TypeSeparator;

typedef struct {
    TypeKeyword type;

} TokenKeyword;

typedef struct  {
    TypeSeparator type;
} TokenSeparator;

typedef struct {
    TypeLiteral type;
    int value;
} TokenLiteral;