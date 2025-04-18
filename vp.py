import psutil
import tkinter as tk
from tkinter import ttk
from time import time, strftime, localtime

# Function to update system metrics
def update_system_metrics():
    cpu_usage = psutil.cpu_percent()
    memory_info = psutil.virtual_memory()
    swap_info = psutil.swap_memory()

    # Update progress bars
    cpu_bar['value'] = cpu_usage
    mem_bar['value'] = memory_info.percent
    swap_bar['value'] = swap_info.percent

    # Update labels with percentages
    cpu_label.config(text=f"{cpu_usage:.1f}%")
    mem_label.config(text=f"{memory_info.percent:.1f}%")
    swap_label.config(text=f"{swap_info.percent:.1f}%")
    
    # Update system info labels
    cpu_info_label.config(text=f"Name: {psutil.cpu_freq().current / 1000:.2f} GHz ({psutil.cpu_count()} Cores)")
    memory_info_label.config(text=f"Size: {memory_info.total / (1024**3):.1f} GB")
    uptime_seconds = int(time() - psutil.boot_time())
    uptime_str = strftime('%H:%M:%S', localtime(uptime_seconds))
    uptime_label.config(text=f"Uptime: {uptime_str}")

    # Schedule the next update
    root.after(1000, update_system_metrics)

# Function to get current system processes
def get_processes():
    processes = []
    for proc in psutil.process_iter(['pid', 'name', 'username', 'memory_info']):
        try:
            processes.append({
                "PID": proc.info['pid'],
                "Name": proc.info['name'],
                "User": proc.info['username'],
                "Memory": f"{proc.info['memory_info'].rss / (1024 * 1024):.2f} MB"
            })
        except (psutil.NoSuchProcess, psutil.AccessDenied, psutil.ZombieProcess):
            pass
    return processes

# Function to update the process list
def update_process_list(tree):
    for item in tree.get_children():
        tree.delete(item)

    processes = get_processes()
    for proc in processes:
        tree.insert("", "end", values=(proc["PID"], proc["Name"], proc["User"], proc["Memory"]))

    root.after(2000, update_process_list, tree)

# Set up the root window
root = tk.Tk()
root.title("Amazing Process Viewer")
root.geometry("900x600")
root.config(bg="#1e1e1e")

# Top frame for system metrics
top_frame = tk.Frame(root, bg="#1e1e1e")
top_frame.pack(fill="x", pady=(10, 5))

# CPU Progress Bar and Label
cpu_text_label = tk.Label(top_frame, text="CPU", font=("Consolas", 12), fg="lightgreen", bg="#1e1e1e")
cpu_text_label.grid(row=0, column=0, padx=5)
cpu_bar = ttk.Progressbar(top_frame, orient="horizontal", length=150, mode="determinate", maximum=100)
cpu_bar.grid(row=0, column=1)
cpu_label = tk.Label(top_frame, text="0.0%", font=("Consolas", 12), fg="white", bg="#1e1e1e")
cpu_label.grid(row=0, column=2, padx=5)

# Memory Progress Bar and Label
mem_text_label = tk.Label(top_frame, text="Mem", font=("Consolas", 12), fg="lightgreen", bg="#1e1e1e")
mem_text_label.grid(row=0, column=3, padx=5)
mem_bar = ttk.Progressbar(top_frame, orient="horizontal", length=150, mode="determinate", maximum=100)
mem_bar.grid(row=0, column=4)
mem_label = tk.Label(top_frame, text="0.0%", font=("Consolas", 12), fg="white", bg="#1e1e1e")
mem_label.grid(row=0, column=5, padx=5)

# Swap (Page File) Progress Bar and Label
swap_text_label = tk.Label(top_frame, text="Pge", font=("Consolas", 12), fg="lightgreen", bg="#1e1e1e")
swap_text_label.grid(row=0, column=6, padx=5)
swap_bar = ttk.Progressbar(top_frame, orient="horizontal", length=150, mode="determinate", maximum=100)
swap_bar.grid(row=0, column=7)
swap_label = tk.Label(top_frame, text="0.0%", font=("Consolas", 12), fg="white", bg="#1e1e1e")
swap_label.grid(row=0, column=8, padx=5)

# System Info Labels
cpu_info_label = tk.Label(top_frame, text="Name: Loading...", font=("Consolas", 12), fg="lightblue", bg="#1e1e1e")
cpu_info_label.grid(row=1, column=0, columnspan=3, sticky="w", padx=10, pady=(5, 0))

memory_info_label = tk.Label(top_frame, text="Size: Loading...", font=("Consolas", 12), fg="lightblue", bg="#1e1e1e")
memory_info_label.grid(row=1, column=3, columnspan=3, sticky="w", padx=10, pady=(5, 0))

uptime_label = tk.Label(top_frame, text="Uptime: 00:00:00", font=("Consolas", 12), fg="lightblue", bg="#1e1e1e")
uptime_label.grid(row=1, column=6, columnspan=3, sticky="w", padx=10, pady=(5, 0))

# Process list title
label = tk.Label(root, text="Current Processes", font=("Arial", 18), fg="white", bg="#1e1e1e")
label.pack(pady=10)

# Frame for the process list
frame = tk.Frame(root, bg="#1e1e1e")
frame.pack(fill="both", expand=True)

# Treeview for displaying processes
tree = ttk.Treeview(frame, columns=("PID", "Name", "User", "Memory"), show="headings", style="Treeview")
tree.pack(fill="both", expand=True, side="left")

# Scrollbar for the treeview
scrollbar = ttk.Scrollbar(frame, orient="vertical", command=tree.yview)
scrollbar.pack(side="right", fill="y")
tree.configure(yscrollcommand=scrollbar.set)

# Define column headings
tree.heading("PID", text="PID", anchor="w")
tree.heading("Name", text="Name", anchor="w")
tree.heading("User", text="User", anchor="w")
tree.heading("Memory", text="Memory", anchor="w")

# Set column widths
tree.column("PID", width=80, anchor="center")
tree.column("Name", width=300, anchor="w")
tree.column("User", width=200, anchor="w")
tree.column("Memory", width=120, anchor="center")

# Treeview styling
style = ttk.Style()
style.theme_use("clam")
style.configure("Treeview", background="#2e2e2e", foreground="white", rowheight=25, font=("Consolas", 10))
style.map("Treeview", background=[('selected', '#5f5f5f')])
style.configure("Treeview.Heading", background="#4d4d4d", foreground="white", font=("Consolas", 10, "bold"))

# Start updating system metrics and process list
update_system_metrics()
update_process_list(tree)

# Start the Tkinter main loop
root.mainloop()   