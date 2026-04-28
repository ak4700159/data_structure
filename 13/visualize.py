import matplotlib.pyplot as plt

# 데이터 읽기
data_plus = []
data_times = []

with open('record.txt', 'r') as f:
    for line in f:
        parts = line.strip().split(', ')
        if len(parts) >= 4:
            n = int(parts[0])          # 확장 시 증가하는 값
            method = int(parts[1])     # 1=PLUS, 2=TIMES
            extensions = int(parts[2]) # 확장 횟수
            interval = int(parts[3])   # 실행 시간
            
            if method == 1:
                data_plus.append((n, interval))
            else:
                data_times.append((n, interval))

# 데이터 정렬
data_plus.sort(key=lambda x: x[0])
data_times.sort(key=lambda x: x[0])

# 데이터 분리
plus_n = [d[0] for d in data_plus]
plus_interval = [d[1] for d in data_plus]

times_n = [d[0] for d in data_times]
times_interval = [d[1] for d in data_times]

# 그래프 생성
plt.figure(figsize=(12, 8))

plt.plot(plus_n, plus_interval, 'b-', label='PLUS (capacity += n)', linewidth=1.5, alpha=0.8)
plt.plot(times_n, times_interval, 'r-', label='TIMES (capacity *= n)', linewidth=1.5, alpha=0.8)

plt.xlabel('n (Expansion Value)', fontsize=12)
plt.ylabel('Interval (Execution Time)', fontsize=12)
plt.title('ArrayList Extension: PLUS vs TIMES\n(X-axis: n = expansion value per extension)', fontsize=14, fontweight='bold')
plt.legend(fontsize=11)
plt.grid(True, alpha=0.3)

plt.tight_layout()
plt.savefig('record_visualization.png', dpi=150, bbox_inches='tight')
print("시각화 완료: record_visualization.png")
print(f"PLUS: {len(data_plus)}개 데이터, TIMES: {len(data_times)}개 데이터")
print(f"PLUS n 범위: {min(plus_n)} ~ {max(plus_n)}")
print(f"TIMES n 범위: {min(times_n)} ~ {max(times_n)}")

print("시각화 완료: record_visualization.png")
print(f"PLUS: {len(data_plus)}개 데이터, TIMES: {len(data_times)}개 데이터")