import time


class Data:
    def __init__(self, id_=0, val=0):
        self.id = long(id_)
        self.value = long(val)

    def __cmp__(self, other):
        return self.value < other.value


class Generator:
    def __init__(self):
        self.a = 48271
        self.c = 0
        self.m = 2147483647
        self.prev = 1

    def gen(self):
        self.prev = (self.prev * self.a + self.c) % self.m
        return self.prev


RecordsNum = 100000000

print ('Building {0} records...'.format(RecordsNum))
start = time.time()
d = [None] * RecordsNum
gen = Generator()

for i in xrange(0, RecordsNum):
    v = gen.gen()
    d[i] = Data(v, v)

print ('Elapsed time: {0} s'.format(int(time.time() - start)))

print ('Sorting {0} records...'.format(RecordsNum))
start = time.time()
d.sort(key=lambda item: item.value)
print ('Elapsed time: {0} s'.format(int(time.time() - start)))

print ('Checking whether the collection is sorted...')
start = time.time()
for i in xrange(0, RecordsNum - 1):
    if d[i].value > d[i + 1].value:
        print ('Not sorted!')
        break
print ('Elapsed time: {0} s'.format(int(time.time() - start)))
