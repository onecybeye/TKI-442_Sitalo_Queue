#include "pch.h"
#include "Queue.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace queue;

namespace UnitTest {
    TEST_CLASS(QueueTest) {
public:

    // Тест: Добавление одного и нескольких элементов в очередь
    TEST_METHOD(Enqueue_SingleAndMultipleValues_FrontIsCorrect) {
        Queue q;
        q.enqueue(10);
        Assert::AreEqual(10, q.front(), L"Первый элемент должен быть 10.");

        q.enqueue(20);
        Assert::AreEqual(10, q.front(), L"Первый элемент должен оставаться 10 после добавления 20.");
    }

    // Тест: Удаление элементов из очереди и проверка порядка
    TEST_METHOD(Dequeue_MultipleValues_ValuesRemovedInFIFOOrder) {
        Queue q;
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);

        Assert::AreEqual(10, q.dequeue(), L"Первым должен быть удалён элемент 10.");
        Assert::AreEqual(20, q.front(), L"Первый элемент после удаления должен быть 20.");

        Assert::AreEqual(20, q.dequeue(), L"Вторым должен быть удалён элемент 20.");
        Assert::AreEqual(30, q.front(), L"Первый элемент после второго удаления должен быть 30.");
    }

    // Тест: Проверка пустоты очереди
    TEST_METHOD(IsEmpty_EmptyQueue_ReturnsTrue) {
        Queue q;
        Assert::IsTrue(q.isEmpty(), L"Очередь должна быть пустой при создании.");
    }

    // Тест: Очередь не пуста после добавления элемента
    TEST_METHOD(IsEmpty_NonEmptyQueue_ReturnsFalse) {
        Queue q;
        q.enqueue(10);
        Assert::IsFalse(q.isEmpty(), L"Очередь не должна быть пустой после добавления элемента.");
    }

    // Тест: Получение элемента из пустой очереди вызывает исключение
    TEST_METHOD(Front_EmptyQueue_ExceptionThrown) {
        Queue q;
        Assert::ExpectException<std::runtime_error>([&q]() { q.front(); },
            L"Ожидается исключение при вызове front() на пустой очереди.");
    }

    // Тест: Удаление элемента из пустой очереди вызывает исключение
    TEST_METHOD(Dequeue_EmptyQueue_ExceptionThrown) {
        Queue q;
        Assert::ExpectException<std::runtime_error>([&q]() { q.dequeue(); },
            L"Ожидается исключение при попытке удалить элемент из пустой очереди.");
    }

    // Тест: Перегрузка оператора << для корректного вывода очереди
    TEST_METHOD(OutputOperator_QueueState_CorrectOutput) {
        Queue q;
        q.enqueue(10);
        q.enqueue(20);
        q.enqueue(30);

        std::ostringstream oss;
        oss << q;

        Assert::AreEqual(std::string("10 20 30"), oss.str(),
            L"Неверный вывод состояния очереди.");
    }

    // Тест: Динамическое изменение размера очереди при добавлении элементов
    TEST_METHOD(Enqueue_ResizeQueue_HandlesCorrectly) {
        Queue q(2); // Начальный размер очереди - 2

        q.enqueue(10);
        q.enqueue(20);

        // Добавление третьего элемента должно вызвать resize
        q.enqueue(30);

        Assert::AreEqual(10, q.front(), L"Первый элемент должен быть 10 после изменения размера.");
        Assert::AreEqual(10, q.dequeue(), L"Извлечение должно вернуть 10.");
        Assert::AreEqual(20, q.front(), L"Первый элемент должен быть 20 после удаления 10.");
    }
    };
}
