import pandas as pd
import numpy as np
import keras
from sklearn.model_selection import train_test_split
from keras.models import Sequential
from keras.layers import Dense, LSTM
from keras.callbacks import EarlyStopping

# Читаем данные из файла
df = pd.read_csv('V9.csv')

# Разделяем данные на обучающую, проверочную и тестовую выборки
X = df[['Mx', 'My', 'Mz', 'Fx', 'Fy', 'Fz']]
y = df['EQV1']

X_train, X_valid, y_train, y_valid = train_test_split(X, y, test_size=0.2, random_state=42)
X_test, _, _, _ = train_test_split(X, y, test_size=0.2, random_state=42)

# Масштабируем данные
min_max_scaler = MinMaxScaler()
X_train = min_max_scaler.fit_transform(X_train)
X_valid = min_max_scaler.transform(X_valid)
X_test = min_max_scaler.transform(X_test)

# Создаем и тренируем полносвязную нейронную сеть
input_dim = X_train.shape[1]
hidden_units = 100
output_dim = 1

fcnn_model = Sequential()
fcnn_model.add(Dense(hidden_units, activation='relu', input_dim=input_dim))
fcnn_model.add(Dense(hidden_units, activation='relu'))
fcnn_model.add(Dense(output_dim, activation='linear'))

fcnn_model.compile(loss='mse', optimizer='adam', metrics=['mae'])
early_stopping = EarlyStopping(monitor='val_loss', patience=10)
history = fcnn_model.fit(X_train, y_train, epochs=100, batch_size=32, validation_data=(X_valid, y_valid), callbacks=[early_stopping])

# Оцениваем качество на валидационном наборе
fcnn_score = fcnn_model.evaluate(X_valid, y_valid)
print("FCNN Validation MAE:", fcnn_score[1])
print("FCNN Validation MSE:", fcnn_score[0])

# Создаем и тренируем LSTM рекуррентную сеть
lstm_model = Sequential()
lstm_model.add(LSTM(hidden_units, return_sequences=True, input_shape=(None, input_dim)))
lstm_model.add(LSTM(hidden_units, return_sequences=False))
lstm_model.add(Dense(output_dim, activation='linear'))

lstm_model.compile(loss='mse', optimizer='adam', metrics=['mae'])
early_stopping = EarlyStopping(monitor='val_loss', patience=10)
history = lstm_model.fit(X_train, y_train, epochs=100, batch_size=32, validation_data=(X_valid, y_valid), callbacks=[early_stopping])

# Оцениваем качество на валидационном наборе
lstm_score = lstm_model.evaluate(X_valid, y_valid)
print("LSTM Validation MAE:", lstm_score[1])
print("LSTM Validation MSE:", lstm_score[0])

# Сравниваем качество моделей
if fcnn_score[1] <= lstm_score[1]:
    best_model = fcnn_model
else:
    best_model = lstm_model

best_model.save('best_model.h5')

# Проводим Grid Search для настроек гиперпараметров
param_grid = {'epochs': range(10, 100, 10)}
grid = GridSearchCV(estimator=best_model, param_grid=param_grid, cv=3, scoring='neg_mean_squared_error')
grid_result = grid.fit(X_train, y_train)

# Получаем лучшие параметры и оцениваем качество на тестовом наборе
best_params = grid_result.best_params_
best_model.set_params(**best_params)
best_model.load_weights('best_model.h5')
best_model.compile(loss='mse', optimizer='adam', metrics=['mae'])

best_score = best_model.evaluate(X_test, y_test)
print("Best Model Test MAE:", best_score[1])
print("Best Model Test MSE:", best_score[0])

# Записываем результаты в файл
with open('results.txt', 'w') as file:
    file.write(f'FCNN Validation MAE: {fcnn_score[1]}\n')
    file.write(f'FCNN Validation MSE: {fcnn_score[0]}\n')
    file.write(f'LSTM Validation MAE: {lstm_score[1]}\n')
    file.write(f'LSTM Validation MSE: {lstm_score[0]}\n')
    file.write(f'Best Model Test MAE: {best_score[1]}\n')
    file.write(f'Best Model Test MSE: {best_score[0]}')