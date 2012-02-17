#include <check.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "config.h"

START_TEST(test_config_get_default)
{
    bloom_config config;
    int res = config_from_filename(NULL, &config);
    fail_unless(res == 0);
    fail_unless(config.tcp_port == 8673);
    fail_unless(config.udp_port == 8674);
    fail_unless(strcmp(config.data_dir, "/tmp/bloomd") == 0);
    fail_unless(strcmp(config.log_level, "DEBUG") == 0);
    fail_unless(config.syslog_log_level == LOG_DEBUG);
    fail_unless(config.initial_capacity == 100000);
    fail_unless(config.default_probability == 1e-4);
    fail_unless(config.scale_size == 4);
    fail_unless(config.probability_reduction == 0.9);
    fail_unless(config.flush_interval == 60);
    fail_unless(config.cold_interval == 3600);
}
END_TEST

START_TEST(test_config_bad_file)
{
    bloom_config config;
    int res = config_from_filename("/tmp/does_not_exist", &config);
    fail_unless(res == -ENOENT);

    // Should get the defaults...
    fail_unless(config.tcp_port == 8673);
    fail_unless(config.udp_port == 8674);
    fail_unless(strcmp(config.data_dir, "/tmp/bloomd") == 0);
    fail_unless(strcmp(config.log_level, "DEBUG") == 0);
    fail_unless(config.syslog_log_level == LOG_DEBUG);
    fail_unless(config.initial_capacity == 100000);
    fail_unless(config.default_probability == 1e-4);
    fail_unless(config.scale_size == 4);
    fail_unless(config.probability_reduction == 0.9);
    fail_unless(config.flush_interval == 60);
    fail_unless(config.cold_interval == 3600);
}
END_TEST

START_TEST(test_config_empty_file)
{
    int fh = open("/tmp/zero_file", O_CREAT|O_RDWR);
    close(fh);

    bloom_config config;
    int res = config_from_filename("/tmp/zero_file", &config);
    fail_unless(res == 0);

    // Should get the defaults...
    fail_unless(config.tcp_port == 8673);
    fail_unless(config.udp_port == 8674);
    fail_unless(strcmp(config.data_dir, "/tmp/bloomd") == 0);
    fail_unless(strcmp(config.log_level, "DEBUG") == 0);
    fail_unless(config.syslog_log_level == LOG_DEBUG);
    fail_unless(config.initial_capacity == 100000);
    fail_unless(config.default_probability == 1e-4);
    fail_unless(config.scale_size == 4);
    fail_unless(config.probability_reduction == 0.9);
    fail_unless(config.flush_interval == 60);
    fail_unless(config.cold_interval == 3600);

    unlink("/tmp/zero_file");
}
END_TEST


