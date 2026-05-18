import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ThreadSafeArrayList<T> {
    private final List<T> list = new ArrayList<>();
    private final ReadWriteLock lock = new ReentrantReadWriteLock();

    public void add(T value) {
        lock.writeLock().lock();

        try {
            list.add(value);
        } finally {
            lock.writeLock().unlock();
        }
    }

    public T get(int index) {
        lock.readLock().lock();

        try {
            return list.get(index);
        } finally {
            lock.readLock().unlock();
        }
    }

    public T remove(int index) {
        lock.writeLock().lock();

        try {
            return list.remove(index);
        } finally {
            lock.writeLock().unlock();
        }
    }

    public int size() {
        lock.readLock().lock();

        try {
            return list.size();
        } finally {
            lock.readLock().unlock();
        }
    }

    public boolean contains(T value) {
        lock.readLock().lock();

        try {
            return list.contains(value);
        } finally {
            lock.readLock().unlock();
        }
    }
}