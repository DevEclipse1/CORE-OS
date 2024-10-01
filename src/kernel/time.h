void sleep(int duration) {
    volatile unsigned long long count = 0;
    unsigned long long end = duration * 100000;
    while (count < end) {
        ++count;
    }
}