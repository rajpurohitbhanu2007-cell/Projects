// ==========================================================================
// Employee Management System - Vanilla JavaScript
// ==========================================================================

// Initial sample data if localStorage is empty
const defaultEmployees = [
  {
    id: 101,
    name: "Aarav Sharma",
    email: "aarav.sharma@company.com",
    department: "Engineering",
    position: "Senior Full Stack Dev",
    salary: 85000,
    status: "Active"
  },
  {
    id: 102,
    name: "Bhanu Rajput",
    email: "bhanu.rajput@company.com",
    department: "Engineering",
    position: "Lead Software Architect",
    salary: 110000,
    status: "Active"
  },
  {
    id: 103,
    name: "Sneha Patel",
    email: "sneha.patel@company.com",
    department: "Product",
    position: "Product Manager",
    salary: 95000,
    status: "Active"
  },
  {
    id: 104,
    name: "Rohan Verma",
    email: "rohan.verma@company.com",
    department: "Marketing",
    position: "SEO & Growth Specialist",
    salary: 60000,
    status: "On Leave"
  },
  {
    id: 105,
    name: "Ananya Iyer",
    email: "ananya.iyer@company.com",
    department: "Human Resources",
    position: "HR Generalist",
    salary: 55000,
    status: "Active"
  },
  {
    id: 106,
    name: "Karan Mehta",
    email: "karan.mehta@company.com",
    department: "Sales",
    position: "Account Executive",
    salary: 50000,
    status: "Inactive"
  }
];

// App State
let employees = [];

// DOM Element References
const employeeTableBody = document.getElementById("employeeTableBody");
const noRecordsFound = document.getElementById("noRecordsFound");
const searchInput = document.getElementById("searchInput");
const departmentFilter = document.getElementById("departmentFilter");
const statusFilter = document.getElementById("statusFilter");

// Stats Elements (Module 4)
const totalEmployeesCount = document.getElementById("totalEmployeesCount");
const activeEmployeesCount = document.getElementById("activeEmployeesCount");
const totalPayrollDisplay = document.getElementById("totalPayrollDisplay");
const averageSalaryDisplay = document.getElementById("averageSalaryDisplay");

// Modal Elements (Module 1)
const employeeModal = document.getElementById("employeeModal");
const openAddModalBtn = document.getElementById("openAddModalBtn");
const closeModalBtn = document.getElementById("closeModalBtn");
const cancelModalBtn = document.getElementById("cancelModalBtn");
const employeeForm = document.getElementById("employeeForm");
const modalTitle = document.getElementById("modalTitle");

const editEmployeeIdInput = document.getElementById("editEmployeeId");
const empIdInput = document.getElementById("empId");
const empNameInput = document.getElementById("empName");
const empEmailInput = document.getElementById("empEmail");
const empDepartmentInput = document.getElementById("empDepartment");
const empPositionInput = document.getElementById("empPosition");
const empSalaryInput = document.getElementById("empSalary");
const empStatusInput = document.getElementById("empStatus");

// ==========================================================================
// Storage Helpers
// ==========================================================================
function loadFromStorage() {
  const stored = localStorage.getItem("ems_employees");
  if (stored) {
    try {
      employees = JSON.parse(stored);
    } catch (e) {
      employees = defaultEmployees;
    }
  } else {
    employees = defaultEmployees;
    saveToStorage();
  }
}

function saveToStorage() {
  localStorage.setItem("ems_employees", JSON.stringify(employees));
}

// ==========================================================================
// MODULE 4: Analytics & Payroll Statistics
// ==========================================================================
function updateAnalytics() {
  const total = employees.length;
  const activeCount = employees.filter((emp) => emp.status === "Active").length;
  const totalPayroll = employees.reduce((sum, emp) => sum + Number(emp.salary || 0), 0);
  const avgSalary = total > 0 ? Math.round(totalPayroll / total) : 0;

  totalEmployeesCount.textContent = total;
  activeEmployeesCount.textContent = activeCount;
  totalPayrollDisplay.textContent = `₹${totalPayroll.toLocaleString("en-IN")}`;
  averageSalaryDisplay.textContent = `₹${avgSalary.toLocaleString("en-IN")}`;
}

// ==========================================================================
// MODULE 2 & 3: Directory Table Rendering, Filters & Search
// ==========================================================================
function getFilteredEmployees() {
  const query = searchInput.value.trim().toLowerCase();
  const selectedDept = departmentFilter.value;
  const selectedStatus = statusFilter.value;

  return employees.filter((emp) => {
    // Search query filter (matches name, position, id, or email)
    const matchesSearch =
      emp.name.toLowerCase().includes(query) ||
      emp.position.toLowerCase().includes(query) ||
      emp.email.toLowerCase().includes(query) ||
      String(emp.id).includes(query);

    // Department filter
    const matchesDept = selectedDept === "ALL" || emp.department === selectedDept;

    // Status filter
    const matchesStatus = selectedStatus === "ALL" || emp.status === selectedStatus;

    return matchesSearch && matchesDept && matchesStatus;
  });
}

function renderTable() {
  const filtered = getFilteredEmployees();
  employeeTableBody.innerHTML = "";

  if (filtered.length === 0) {
    noRecordsFound.style.display = "block";
    return;
  }
  noRecordsFound.style.display = "none";

  filtered.forEach((emp) => {
    const tr = document.createElement("tr");

    // Status class mapping
    let statusClass = "active";
    if (emp.status === "On Leave") statusClass = "on-leave";
    if (emp.status === "Inactive") statusClass = "inactive";

    tr.innerHTML = `
      <td><strong>#${emp.id}</strong></td>
      <td>
        <span class="emp-name-cell">${escapeHtml(emp.name)}</span>
        <span class="emp-email-sub">${escapeHtml(emp.email)}</span>
      </td>
      <td>${escapeHtml(emp.department)}</td>
      <td>${escapeHtml(emp.position)}</td>
      <td>₹${Number(emp.salary).toLocaleString("en-IN")}</td>
      <td>
        <span class="status-badge ${statusClass}">${emp.status}</span>
      </td>
      <td>
        <div class="actions-cell">
          <button class="btn-sm btn-edit" onclick="handleEditEmployee(${emp.id})">Edit</button>
          <button class="btn-sm btn-delete" onclick="handleDeleteEmployee(${emp.id})">Delete</button>
        </div>
      </td>
    `;
    employeeTableBody.appendChild(tr);
  });
}

function escapeHtml(text) {
  const div = document.createElement("div");
  div.textContent = text || "";
  return div.innerHTML;
}

// ==========================================================================
// MODULE 1: Employee Registration (Add / Edit / Delete)
// ==========================================================================
function openAddModal() {
  modalTitle.textContent = "Add New Employee";
  editEmployeeIdInput.value = "";
  employeeForm.reset();
  empIdInput.disabled = false;

  // Auto-suggest next ID
  const maxId = employees.length > 0 ? Math.max(...employees.map((e) => Number(e.id))) : 100;
  empIdInput.value = maxId + 1;

  employeeModal.style.display = "flex";
}

function handleEditEmployee(id) {
  const emp = employees.find((e) => e.id === id);
  if (!emp) return;

  modalTitle.textContent = "Edit Employee Details";
  editEmployeeIdInput.value = emp.id;
  empIdInput.value = emp.id;
  empIdInput.disabled = true; // Lock ID during update

  empNameInput.value = emp.name;
  empEmailInput.value = emp.email;
  empDepartmentInput.value = emp.department;
  empPositionInput.value = emp.position;
  empSalaryInput.value = emp.salary;
  empStatusInput.value = emp.status;

  employeeModal.style.display = "flex";
}

function closeModal() {
  employeeModal.style.display = "none";
  employeeForm.reset();
}

function handleDeleteEmployee(id) {
  const emp = employees.find((e) => e.id === id);
  if (!emp) return;

  const confirmed = confirm(`Are you sure you want to delete employee "${emp.name}" (ID: ${emp.id})?`);
  if (!confirmed) return;

  employees = employees.filter((e) => e.id !== id);
  saveToStorage();
  updateAnalytics();
  renderTable();
}

// Handle Form Submission (Add or Update)
employeeForm.addEventListener("submit", (e) => {
  e.preventDefault();

  const isEdit = Boolean(editEmployeeIdInput.value);
  const id = Number(empIdInput.value);
  const name = empNameInput.value.trim();
  const email = empEmailInput.value.trim();
  const department = empDepartmentInput.value;
  const position = empPositionInput.value.trim();
  const salary = Number(empSalaryInput.value);
  const status = empStatusInput.value;

  if (!isEdit) {
    // Check duplicate ID
    const exists = employees.some((e) => e.id === id);
    if (exists) {
      alert(`[Error] An employee with ID ${id} already exists! Please use a unique ID.`);
      return;
    }

    employees.push({
      id,
      name,
      email,
      department,
      position,
      salary,
      status
    });
  } else {
    // Update existing
    const editId = Number(editEmployeeIdInput.value);
    const index = employees.findIndex((e) => e.id === editId);
    if (index !== -1) {
      employees[index] = {
        id: editId,
        name,
        email,
        department,
        position,
        salary,
        status
      };
    }
  }

  saveToStorage();
  updateAnalytics();
  renderTable();
  closeModal();
});

// Event Listeners for Search & Filters
searchInput.addEventListener("input", renderTable);
departmentFilter.addEventListener("change", renderTable);
statusFilter.addEventListener("change", renderTable);

// Modal triggers
openAddModalBtn.addEventListener("click", openAddModal);
closeModalBtn.addEventListener("click", closeModal);
cancelModalBtn.addEventListener("click", closeModal);

// Close modal if backdrop clicked
window.addEventListener("click", (e) => {
  if (e.target === employeeModal) {
    closeModal();
  }
});

// Initialization
document.addEventListener("DOMContentLoaded", () => {
  loadFromStorage();
  updateAnalytics();
  renderTable();
});
