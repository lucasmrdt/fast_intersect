import random
import time
import my_set
import sys


class Element:
    def __init__(self, val: int):
        self.val = val

    def __hash__(self) -> int:
        return self.val


def time_fct(l1, l2, fct):
    start = time.time()
    output = fct(l1, l2)
    # output = timeout(fct, args=(l1, l2), timeout_duration=10)
    diff = time.time() - start
    if output is None:
        return float('inf')
    return diff


def run(size, fct):
    l1 = [random.randint(0, size) for i in range(size)]
    l2 = [random.randint(0, size) for i in range(size)]
    return time_fct(l1, l2, fct)

# from https://stackoverflow.com/a/13821695/10203321


def timeout(func, args=(), kwargs={}, timeout_duration=1, default=None):
    import signal

    class TimeoutError(Exception):
        pass

    def handler(signum, frame):
        raise TimeoutError()

    # set the timeout handler
    signal.signal(signal.SIGALRM, handler)
    signal.alarm(timeout_duration)
    try:
        result = func(*args, **kwargs)
    except TimeoutError as exc:
        result = default
    finally:
        signal.alarm(0)

    return result


print(run(10000, my_set.intersection))
