#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};




// Corresponds to lightning__srv__LocCmd_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
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
    pub map_id: std::string::String,

    /// 时间戳
    pub header: std_msgs::msg::Header,

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
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::LocCmd_Request::default())
  }
}

impl rosidl_runtime_rs::Message for LocCmd_Request {
  type RmwMsg = super::srv::rmw::LocCmd_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        id: msg.id,
        x: msg.x,
        y: msg.y,
        z: msg.z,
        map_id: msg.map_id.as_str().into(),
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Owned(msg.header)).into_owned(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      id: msg.id,
      x: msg.x,
      y: msg.y,
      z: msg.z,
        map_id: msg.map_id.as_str().into(),
        header: std_msgs::msg::Header::into_rmw_message(std::borrow::Cow::Borrowed(&msg.header)).into_owned(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      id: msg.id,
      x: msg.x,
      y: msg.y,
      z: msg.z,
      map_id: msg.map_id.to_string(),
      header: std_msgs::msg::Header::from_rmw_message(msg.header),
    }
  }
}


// Corresponds to lightning__srv__LocCmd_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct LocCmd_Response {
    /// 为0表示成功
    pub result: u32,

}



impl Default for LocCmd_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::LocCmd_Response::default())
  }
}

impl rosidl_runtime_rs::Message for LocCmd_Response {
  type RmwMsg = super::srv::rmw::LocCmd_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        result: msg.result,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      result: msg.result,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      result: msg.result,
    }
  }
}


// Corresponds to lightning__srv__SaveMap_Request

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Request {
    /// 地图名称（唯一标识）
    pub map_id: std::string::String,

}



impl Default for SaveMap_Request {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SaveMap_Request::default())
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Request {
  type RmwMsg = super::srv::rmw::SaveMap_Request;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        map_id: msg.map_id.as_str().into(),
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      map_id: msg.map_id.to_string(),
    }
  }
}


// Corresponds to lightning__srv__SaveMap_Response

// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct SaveMap_Response {
    /// 为0时成功， 1保存地图已经在运行 2图像渲染重置失败 3地图数据为空，无法保存，4扩图定位失败
    pub response: u32,

}



impl Default for SaveMap_Response {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::srv::rmw::SaveMap_Response::default())
  }
}

impl rosidl_runtime_rs::Message for SaveMap_Response {
  type RmwMsg = super::srv::rmw::SaveMap_Response;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        response: msg.response,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      response: msg.response,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      response: msg.response,
    }
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


