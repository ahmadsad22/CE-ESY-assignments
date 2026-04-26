#include <stdio.h>
#include <string.h>

/* * ملاحظة لاختبار حجم المخزن:
 * - اجعل SIZE = 50 للعمل بشكل طبيعي.
 * - اجعل SIZE = 5 لاختبار حالة الامتلاء (Overflow).
 */
#define SIZE 10

// تعريف هيكل البيانات للمخزن الدائري
typedef struct {
    char data[SIZE];
    int head;  
    int tail; 
    int count; 
} CircularBuffer;

// 1. دالة تهيئة المخزن وتصفير المؤشرات
void init_buffer(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// 2. دالة الكتابة (إدخال بيانات) ومعالجة حالة الامتلاء (Overflow)
int write_buffer(CircularBuffer *cb, char value) {
    if (cb->count == SIZE) {
        printf("\n[Overflow Error] Buffer is full! Cannot write: '%c'\n", value);
        return -1; 
    }
    cb->data[cb->head] = value;
    cb->head = (cb->head + 1) % SIZE; // العملية الحسابية التي تجعل المسار دائرياً
    cb->count++;
    return 0;
}

// 3. دالة القراءة (استخراج بيانات) ومعالجة حالة الفراغ (Underflow)
int read_buffer(CircularBuffer *cb, char *value) {
    if (cb->count == 0) {
        printf("\n[Underflow Error] Buffer is empty! Nothing to read.\n");
        return -1; 
    }
    *value = cb->data[cb->tail];
    cb->tail = (cb->tail + 1) % SIZE; // الحركة الدائرية لمؤشر القراءة
    cb->count--;
    return 0;
}


int main() {
    CircularBuffer cb;
    init_buffer(&cb);

    char name[50];
    char combined[100];
    char output_char;

    //  أ. طلب من المستخدم ادخال الاسم 
    printf("Enter your name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // حذف سطر الإدخال الزائد

    // ب. دمج الاسم مع اللاحقة المطلوبة
    sprintf(combined, "%s ESY-CE", name);
    printf("Final string to process: %s\n", combined);

    // ج. تخزين السلسلة النصية حرفاً بحرف في المخزن
    printf("\n--- Writing to Buffer ---\n");
    for (int i = 0; i < (int)strlen(combined); i++) {
        if (write_buffer(&cb, combined[i]) == 0) {
            printf("Stored: '%c'\n", combined[i]);
        }
    }

    // د. قراءة البيانات وعرض النتيجة النهائية
    printf("\n--- Reading from Buffer ---\nResult: ");
    while (cb.count > 0) {
        if (read_buffer(&cb, &output_char) == 0) {
            printf("%c", output_char);
        }
    }
    printf("\n");

    // هـ. التحقق من أن المخزن أصبح فارغاً بعد القراءة
    if (cb.count == 0) {
        printf("\n[Success] Buffer is now empty.\n");
        // محاولة قراءة إضافية لإظهار رسالة الـ Underflow (تأكيد صحة الحل)
        read_buffer(&cb, &output_char); 
    }

    return 0;
}