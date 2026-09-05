#include "tester.h"

int test_ft_strlen(void)
{
    const char *samples[] = {
        "",
        "\0",
        "\0\0",
        "a",
        "hello",
        "hello world",
        "hello\0 world"
    };

    const size_t sample_count = sizeof(samples) / sizeof(*samples);

    for (size_t i = 0; i < sample_count; ++i)
        assert(ft_strlen(samples[i]) == strlen(samples[i]));

    return (0);
}

int main(void)
{
    return (test_ft_strlen());
}
