import pandas as pd
import matplotlib.pyplot as plt

def create_plot(df, operation_name, filename, title, ylabel):
    # Фильтруем данные по типу операции
    data = df[df['Operation'] == operation_name]
    
    if data.empty:
        return

    plt.figure(figsize=(10, 6))
    
    # Строим линию для каждой структуры данных
    for structure in data['Structure'].unique():
        subset = data[data['Structure'] == structure]
        plt.plot(subset['N'], subset['Avg_Operations'], marker='o', label=structure, linewidth=2)
    
    plt.title(title, fontsize=14)
    plt.xlabel('Размер массива (N)', fontsize=12)
    plt.ylabel(ylabel, fontsize=12)
    plt.legend(bbox_to_anchor=(1.05, 1), loc='upper left')
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.tight_layout() # Чтобы легенда не обрезалась
    
    # Сохраняем график
    plt.savefig(filename)
    plt.close()

try:
    # Загружаем данные
    df = pd.read_csv('results.csv')
    
    # 1. График для операций построения
    create_plot(df, 'Build', 'build_graph.png', 
                'Асимптотика построения структур данных', 
                'Количество операций (Build)')
    
    # 2. График для запросов
    create_plot(df, 'Query', 'query_graph.png', 
                'Асимптотика выполнения запроса (RMQ/RSQ)', 
                'Среднее количество операций на запрос')

    # 3. График для обновлений (если есть)
    create_plot(df, 'Update', 'update_graph.png', 
                'Асимптотика обновления элемента', 
                'Среднее количество операций на обновление')
                
    print("✅ Графики успешно построены и сохранены как PNG файлы!")

except FileNotFoundError:
    print("❌ Ошибка: Файл 'results.csv' не найден. Сначала запустите C++ программу.")
except Exception as e:
    print(f"❌ Произошла ошибка: {e}")