# CMakeLists.txt of Simple encoder pcnt component

# Source files directories
set(SIMPLE_ENCODER_PCNT_SRC_DIRS
    "."
    "Button/"
)

# Head files directories
set(SIMPLE_ENCODER_PCNT_INC_DIRS
    "."
    "Button/"
)

# Public component requirement
set(SIMPLE_ENCODER_PCNT_REQUIRES
    "driver"
    "esp_timer"
)

# Private component requirement
set(SIMPLE_ENCODER_PCNT_PRIV_REQUIRES
)

# Register component
idf_component_register(SRC_DIRS ${SIMPLE_ENCODER_PCNT_SRC_DIRS}
                  INCLUDE_DIRS ${SIMPLE_ENCODER_PCNT_INC_DIRS}
                  REQUIRES ${SIMPLE_ENCODER_PCNT_REQUIRES}
                  PRIV_REQUIRES ${SIMPLE_ENCODER_PCNT_PRIV_REQUIRES}
)
