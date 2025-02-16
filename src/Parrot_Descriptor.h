#define TUD_HID_REPORT_DESC_3DMOUSE(...)                    \
    HID_USAGE_PAGE(HID_USAGE_PAGE_DESKTOP),                 \
        HID_USAGE(HID_USAGE_DESKTOP_MULTI_AXIS_CONTROLLER), \
        HID_COLLECTION(HID_COLLECTION_APPLICATION),         \
        HID_COLLECTION(HID_COLLECTION_PHYSICAL),            \
        HID_REPORT_ID(1)                                    \
            HID_LOGICAL_MIN_N(-350, 2),                     \
        HID_LOGICAL_MAX_N(350, 2),                          \
        HID_PHYSICAL_MIN_N(-1400, 2),                       \
        HID_PHYSICAL_MAX_N(1400, 2),                        \
        HID_UNIT_EXPONENT(0x0C),                            \
        HID_UNIT(0x11),                                     \
        HID_USAGE(0x30),                                    \
        HID_USAGE(0x31),                                    \
        HID_USAGE(0x32),                                    \
        HID_REPORT_SIZE(16),                                \
        HID_REPORT_COUNT(3),                                \
        HID_INPUT(0x06),                                    \
        HID_COLLECTION_END,                                 \
        HID_COLLECTION(HID_COLLECTION_PHYSICAL),            \
        HID_REPORT_ID(2)                                    \
            HID_USAGE(0x33),                                \
        HID_USAGE(0x34),                                    \
        HID_USAGE(0x35),                                    \
        HID_REPORT_SIZE(16),                                \
        HID_REPORT_COUNT(3),                                \
        HID_INPUT(0x06),                                    \
        HID_COLLECTION_END,                                 \
        HID_COLLECTION(HID_COLLECTION_PHYSICAL),            \
        HID_REPORT_ID(3)                                    \
            HID_USAGE_PAGE(HID_USAGE_PAGE_DESKTOP),         \
        HID_USAGE_PAGE(HID_USAGE_PAGE_BUTTON),              \
        HID_USAGE_MIN(0x01),                                \
        HID_USAGE_MAX(0x03),                                \
        HID_LOGICAL_MIN(0),                                 \
        HID_LOGICAL_MAX(1),                                 \
        HID_PHYSICAL_MIN(0),                                \
        HID_PHYSICAL_MAX(1),                                \
        HID_REPORT_SIZE(1),                                 \
        HID_REPORT_COUNT(3),                                \
        HID_INPUT(0x02),                                    \
        HID_REPORT_COUNT(1),                                \
        HID_INPUT(0x03),                                    \
        HID_USAGE_MIN(0x05),                                \
        HID_USAGE_MAX(0x06),                                \
        HID_REPORT_COUNT(2),                                \
        HID_INPUT(0x02),                                    \
        HID_REPORT_COUNT(2),                                \
        HID_INPUT(0x03),                                    \
        HID_USAGE(0x09),                                    \
        HID_REPORT_COUNT(1),                                \
        HID_INPUT(0x02),                                    \
        HID_REPORT_COUNT(3),                                \
        HID_INPUT(0x03),                                    \
        HID_USAGE_MIN(0x0D),                                \
        HID_USAGE_MAX(0x10),                                \
        HID_REPORT_COUNT(4),                                \
        HID_INPUT(0x02),                                    \
        HID_REPORT_COUNT(6),                                \
        HID_INPUT(0x03),                                    \
        HID_USAGE_MIN(0x17),                                \
        HID_USAGE_MAX(0x1B),                                \
        HID_REPORT_COUNT(5),                                \
        HID_INPUT(0x02),                                    \
        HID_REPORT_COUNT(21),                               \
        HID_INPUT(0x03),                                    \
        HID_COLLECTION_END,                                 \
        HID_COLLECTION(HID_COLLECTION_LOGICAL),             \
        HID_REPORT_ID(31)                                   \
            HID_USAGE_PAGE_N(HID_USAGE_PAGE_VENDOR, 2),     \
        HID_USAGE(0x02),                                    \
        HID_LOGICAL_MIN(0x00),                              \
        HID_LOGICAL_MAX_N(0xff, 2),                         \
        HID_REPORT_SIZE(8),                                 \
        HID_REPORT_COUNT(63),                               \
        HID_OUTPUT(HID_DATA | HID_VARIABLE | HID_ABSOLUTE), \
        HID_COLLECTION_END,                                 \
        HID_COLLECTION_END
