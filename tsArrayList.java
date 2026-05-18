import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ThreadSafeArrayList<T> {
    private final List<T> list = new ArrayList<>();
    private final ReadWriteLock lock = new ReentrantReadWriteLock(); // Instanciamos o ReadWriteLock

    public void add(T value) {
        lock.writeLock().lock(); // Para o add, só precisamos travar o write lock, que faz com 
        // que operações de inserção e remoção sejam executadas uma por vez na thread
        // já que não podemos ter duas operações dessas acontecendo ao mesmo tempo

        try { // Tento adicionar na lista
            list.add(value);
        } finally {
            lock.writeLock().unlock(); // Desbloqueio pra ficar disponível para a próxima thread
        }
    }

    // Aqui nesse caso temos uma operação de leitura
    public T get(int index) {
        lock.readLock().lock(); // Usamos o método do readlock, que permite com que
        // operações de leitura aconteçam simultaneamente entre as threads

        try { // Tento pegar o índice, e mesmo se der erro, eu 
            return list.get(index);
        } finally {
            lock.readLock().unlock(); // desbloqueio para ficar disponível para uma operação de escrita
        }
    }

    public T remove(int index) { // Aqui seguimos a mesma lógica do write lock, já que
        lock.writeLock().lock(); // duas operações de escrita não podem ocorrer simultaneamente

        try {
            return list.remove(index);
        } finally {
            lock.writeLock().unlock();
        }
    }

    public int size() { // Método de leitura, usamos o readlock
        lock.readLock().lock();

        try {
            return list.size();
        } finally {
            lock.readLock().unlock();
        }
    }

    public boolean contains(T value) { // Método de leitura, usamos o readlock
        lock.readLock().lock();

        try {
            return list.contains(value);
        } finally {
            lock.readLock().unlock();
        }
    }
}