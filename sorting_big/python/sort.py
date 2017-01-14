import time

class Data:
    def __init__(self, id, val):
        self.id = long(id)
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


#RecordsNum = 1000
RecordsNum = 100000000

print ('Building {0} records...'.format(RecordsNum))
start = time.time()
d = []
gen = Generator()
for i in xrange(0, RecordsNum):
    v = gen.gen()
    d.append(Data(v, v))
print ('Elapsed time: {0} s'.format(int(time.time() - start)))

print ('Sorting {0} records...'.format(RecordsNum))
start = time.time()
d.sort(key=lambda v: v.value, reverse=True)
print ('Elapsed time: {0} s'.format(int(time.time() - start)))

print ('Checking whether the collection is sorted...')
start = time.time()
for i in xrange(0, RecordsNum - 1):
    if d[i] > d[i+1]:
        print ('Not sorted!')
        break
print ('Elapsed time: {0} s'.format(int(time.time() - start)))

