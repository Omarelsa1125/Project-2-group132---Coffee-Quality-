## 🎯 Purpose
This project was designed to analyze how sorting algorithm choice affects runtime efficiency on large datasets. By applying Merge Sort and Quick Sort to the same coffee-quality dataset, we demonstrate trade-offs in performance and memory usage under real-world data conditions.

## ⚙️ Algorithm Details
- **Merge Sort:** Divide-and-conquer algorithm that splits data recursively and merges sorted halves. Guarantees O(n log n) time complexity.  
- **Quick Sort:** Partition-based algorithm that sorts in place using pivots. Average O(n log n), but can degrade to O(n²) in worst cases.  

##  GUI Description
The program uses a **Qt6 GUI** with the following components:
- **Main Menu:** Buttons for “Start,” “Compare Sorts,” and “Exit.”  
- **Progress Bar:** Shows algorithm progress with simulated delay.  
- **Result Display:** Displays total runtime for both algorithms side by side.  
- **Coffee-Themed Background:** Custom brown tones and `bean.jpg` icon for theme consistency.
  
If the image doesn’t show up, check your structure:
Project-2-group132---Coffee-Quality-/
┣ 📂 icons/
┃ ┣ bean.jpg
┃ ┗ gui_preview.png
┣ 📂 resources/
┃ ┗ coffee_data.csv
┣ 📂 build/
┣ 📜 main.cpp
┣ 📜 functions.cpp
┣ 📜 functions.h
┣ 📜 CMakeLists.txt
┗ 📜 README.md
