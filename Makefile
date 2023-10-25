# Compilateur C++
CXX = g++

# Options de compilation
CXXFLAGS = -std=c++11 -Wall

# Répertoires des fichiers source et d'en-tête
SRC_DIR = src
INC_DIR = include

# Noms des fichiers source
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Noms des fichiers d'en-tête
HEADERS = $(wildcard $(INC_DIR)/*.h)

# Noms de la cible exécutable
TARGET = ProjetPOO

# Règle par défaut
all: $(TARGET)

# Règle de construction de la cible
$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -o $(TARGET) $(SRCS)

# Règle pour nettoyer les fichiers générés
clean:
	rm -f $(TARGET)

# Règle pour supprimer les fichiers objets (facultatif)
clean-obj:
	rm -f *.o

