#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "lightning__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__LocCmd_Request() -> *const std::ffi::c_void;
}

#[link(name = "lightning__rosidl_generator_c")]
extern "C" {
    fn lightning__srv__LocCmd_Request__init(msg: *mut LocCmd_Request) -> bool;
    fn lightning__srv__LocCmd_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocCmd_Request>, size: usize) -> bool;
    fn lightning__srv__LocCmd_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocCmd_Request>);
    fn lightning__srv__LocCmd_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocCmd_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<LocCmd_Request>) -> bool;
}

// Corresponds to lightning__srv__LocCmd_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocCmd_Request {
    /// 命令id
    pub id: u8,

    /// 重定位点坐标x
    pub x: f64,

    /// 重定位点坐标x
    pub y: f64,

    /// 重定位点坐标x
    pub z: f64,

    /// 地图路径
    pub map_id: rosidl_runtime_rs::String,

    /// 时间戳
    pub header: std_msgs::msg::rmw::Header,

}

impl LocCmd_Request {
    /// 设置地图
    pub const CMD_LOC_SET_MAP: u8 = 1;

    /// 设置重定位姿，参数由x y yaw 给出
    pub const CMD_LOC_INIT_POSE: u8 = 3;

    /// 设置重定位点列表，由建图工具设置并保存成队列
    pub const CMD_LOC_INIT_LIST: u8 = 4;

}


impl Default for LocCmd_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !lightning__srv__LocCmd_Request__init(&mut msg as *mut _) {
        panic!("Call to lightning__srv__LocCmd_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocCmd_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__LocCmd_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__LocCmd_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__LocCmd_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocCmd_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocCmd_Request where Self: Sized {
  const TYPE_NAME: &'static str = "lightning/srv/LocCmd_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__LocCmd_Request() }
  }
}


#[link(name = "lightning__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__LocCmd_Response() -> *const std::ffi::c_void;
}

#[link(name = "lightning__rosidl_generator_c")]
extern "C" {
    fn lightning__srv__LocCmd_Response__init(msg: *mut LocCmd_Response) -> bool;
    fn lightning__srv__LocCmd_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<LocCmd_Response>, size: usize) -> bool;
    fn lightning__srv__LocCmd_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<LocCmd_Response>);
    fn lightning__srv__LocCmd_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<LocCmd_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<LocCmd_Response>) -> bool;
}

// Corresponds to lightning__srv__LocCmd_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocCmd_Response {
    /// 为0表示成功
    pub result: u32,

}



impl Default for LocCmd_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !lightning__srv__LocCmd_Response__init(&mut msg as *mut _) {
        panic!("Call to lightning__srv__LocCmd_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for LocCmd_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__LocCmd_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__LocCmd_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__LocCmd_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for LocCmd_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for LocCmd_Response where Self: Sized {
  const TYPE_NAME: &'static str = "lightning/srv/LocCmd_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__LocCmd_Response() }
  }
}


#[link(name = "lightning__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__SaveMap_Request() -> *const std::ffi::c_void;
}

#[link(name = "lightning__rosidl_generator_c")]
extern "C" {
    fn lightning__srv__SaveMap_Request__init(msg: *mut SaveMap_Request) -> bool;
    fn lightning__srv__SaveMap_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Request>, size: usize) -> bool;
    fn lightning__srv__SaveMap_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Request>);
    fn lightning__srv__SaveMap_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SaveMap_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Request>) -> bool;
}

// Corresponds to lightning__srv__SaveMap_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Request {
    /// 地图名称（唯一标识）
    pub map_id: rosidl_runtime_rs::String,

}



impl Default for SaveMap_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !lightning__srv__SaveMap_Request__init(&mut msg as *mut _) {
        panic!("Call to lightning__srv__SaveMap_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SaveMap_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__SaveMap_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__SaveMap_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__SaveMap_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SaveMap_Request where Self: Sized {
  const TYPE_NAME: &'static str = "lightning/srv/SaveMap_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__SaveMap_Request() }
  }
}


#[link(name = "lightning__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__SaveMap_Response() -> *const std::ffi::c_void;
}

#[link(name = "lightning__rosidl_generator_c")]
extern "C" {
    fn lightning__srv__SaveMap_Response__init(msg: *mut SaveMap_Response) -> bool;
    fn lightning__srv__SaveMap_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Response>, size: usize) -> bool;
    fn lightning__srv__SaveMap_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Response>);
    fn lightning__srv__SaveMap_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<SaveMap_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<SaveMap_Response>) -> bool;
}

// Corresponds to lightning__srv__SaveMap_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Response {
    /// 为0时成功， 1保存地图已经在运行 2图像渲染重置失败 3地图数据为空，无法保存，4扩图定位失败
    pub response: u32,

}



impl Default for SaveMap_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !lightning__srv__SaveMap_Response__init(&mut msg as *mut _) {
        panic!("Call to lightning__srv__SaveMap_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for SaveMap_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__SaveMap_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__SaveMap_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { lightning__srv__SaveMap_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for SaveMap_Response where Self: Sized {
  const TYPE_NAME: &'static str = "lightning/srv/SaveMap_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__lightning__srv__SaveMap_Response() }
  }
}






#[link(name = "lightning__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__lightning__srv__LocCmd() -> *const std::ffi::c_void;
}

// Corresponds to lightning__srv__LocCmd
#[allow(missing_docs, non_camel_case_types)]
pub struct LocCmd;

impl rosidl_runtime_rs::Service for LocCmd {
    type Request = LocCmd_Request;
    type Response = LocCmd_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__lightning__srv__LocCmd() }
    }
}




#[link(name = "lightning__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__lightning__srv__SaveMap() -> *const std::ffi::c_void;
}

// Corresponds to lightning__srv__SaveMap
#[allow(missing_docs, non_camel_case_types)]
pub struct SaveMap;

impl rosidl_runtime_rs::Service for SaveMap {
    type Request = SaveMap_Request;
    type Response = SaveMap_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__lightning__srv__SaveMap() }
    }
}


