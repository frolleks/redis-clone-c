const char *encode_simple_string(const char *str);
const char *encode_bulk_string(const char *str);
const char *encode_integer(int num);
const char *encode_array(const char *arr[], int size);
const char *encode_error(const char *str);