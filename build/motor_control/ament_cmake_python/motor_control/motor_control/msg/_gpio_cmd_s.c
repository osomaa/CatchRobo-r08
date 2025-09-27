// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from motor_control:msg/GpioCmd.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "motor_control/msg/detail/gpio_cmd__struct.h"
#include "motor_control/msg/detail/gpio_cmd__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool motor_control__msg__gpio_cmd__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[36];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("motor_control.msg._gpio_cmd.GpioCmd", full_classname_dest, 35) == 0);
  }
  motor_control__msg__GpioCmd * ros_message = _ros_message;
  {  // pin_index
    PyObject * field = PyObject_GetAttrString(_pymsg, "pin_index");
    if (!field) {
      return false;
    }
    assert(PyLong_Check(field));
    ros_message->pin_index = (int32_t)PyLong_AsLong(field);
    Py_DECREF(field);
  }
  {  // toggle
    PyObject * field = PyObject_GetAttrString(_pymsg, "toggle");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->toggle = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * motor_control__msg__gpio_cmd__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of GpioCmd */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("motor_control.msg._gpio_cmd");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "GpioCmd");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  motor_control__msg__GpioCmd * ros_message = (motor_control__msg__GpioCmd *)raw_ros_message;
  {  // pin_index
    PyObject * field = NULL;
    field = PyLong_FromLong(ros_message->pin_index);
    {
      int rc = PyObject_SetAttrString(_pymessage, "pin_index", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // toggle
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->toggle ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "toggle", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
