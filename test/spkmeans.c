#include "../src/spkmeans.h"
#include "../src/myIO.h"
#include <assert.h>
#include <stdio.h>

void test_run() {
    run(WAM, "test/spk_samp3.txt");
    printf("test run DONE\n");
}

int main(int argc, char **argv) {
    test_run();
    return 0;
}