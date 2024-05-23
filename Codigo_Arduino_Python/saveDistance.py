import serial,time 
import json

# Función para obtener el último ID utilizado
def get_last_id(file_path):
    try:
        with open(file_path, 'r') as json_file:
            data = json.load(json_file)
            if data:
                return max(item["id_Sensores_Data"] for item in data)
    except:
        return 0
    return 0

# Configurar la conexión serial
arduino = serial.Serial('COM3', 9600)
time.sleep(2)  # Esperar a que se establezca la conexión

# Archivo JSON
file_path = 'BD.json'

# Obtener el último ID utilizado
last_id = get_last_id(file_path)
id = last_id + 1

# Número de iteraciones
iterations = 10

# Lista para almacenar los datos nuevos
data_json = []

while iterations>0: 
    
    data = arduino.readline()
    try:
        distancia=int(data)

        # Crear un diccionario para los datos
        data_dict = {
            "id_Sensores_Data": id,
            "distancia (cm)": distancia,
            "rgb": {
                "r": 100,
                "g": 30,
                "b": 20
            }
        }

        # Añadir el diccionario a la lista
        data_json.append(data_dict)

        id += 1
        print(distancia)
    except:
        print("error")
    
    iterations-=1

try:
    with open(file_path, 'r') as json_file:
        existing_data = json.load(json_file)
    data_json = existing_data + data_json
except:
    print("No existe json")
    print("Creando Json")

try:
    # Guardar los datos en un archivo JSON
    with open(file_path, 'w') as json_file:
        json.dump(data_json, json_file, indent=4)
except:
    print("Fallo en abrir o crear", file_path)

print("Datos guardados en data.json")

arduino.close()