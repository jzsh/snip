
/**
 * CHECK_NULL_ARG internal macro with return
 */

#define DPRINT printf

enum error_code {
    ERR_OK=0,
    ERR_INVAL_ARG,
    ERR_NOT_FOUND,
    ERR_NOMEM,
};

#define CHECK_NULL_ARG__INTERNAL(ARG) \
    if (NULL == ARG) { \
        DPRINT("NULL value detected for %s argument of %s", #ARG, __func__); \
        return ERR_INVAL_ARG; \
    } \

/**
 * CHECK_NULL_ARG internal macro without return
 */
#define CHECK_NULL_ARG_VOID__INTERNAL(ARG) \
    if (NULL == ARG) { \
        DPRINT("NULL value detected for %s argument of %s", #ARG, __func__); \
        return; \
    } \

/**
 * CHECK_NULL_ARG internal macro with setting rc
 */
#define CHECK_NULL_ARG_NORET__INTERNAL(RC, ARG) \
    if (NULL == ARG) { \
        DPRINT("NULL value detected for %s argument of %s", #ARG, __func__); \
        RC = SR_ERR_INVAL_ARG; \
    } \


/**
 * CHECK_NULL_ARG one argument macro with return
 */
#define CHECK_NULL_ARG(ARG) \
    do { \
        CHECK_NULL_ARG__INTERNAL(ARG) \
    } while(0)

/**
 * CHECK_NULL_ARG two arguments macro with return
 */
#define CHECK_NULL_ARG2(ARG1, ARG2) \
    do { \
        CHECK_NULL_ARG__INTERNAL(ARG1) \
        CHECK_NULL_ARG__INTERNAL(ARG2) \
    } while(0)

/**
 * CHECK_NULL_ARG three arguments macro with return
 */
#define CHECK_NULL_ARG3(ARG1, ARG2, ARG3) \
    do { \
        CHECK_NULL_ARG__INTERNAL(ARG1) \
        CHECK_NULL_ARG__INTERNAL(ARG2) \
        CHECK_NULL_ARG__INTERNAL(ARG3) \
    } while(0)


/**
 * CHECK_NULL_ARG four arguments macro with return
 */
#define CHECK_NULL_ARG4(ARG1, ARG2, ARG3, ARG4) \
    do { \
        CHECK_NULL_ARG__INTERNAL(ARG1) \
        CHECK_NULL_ARG__INTERNAL(ARG2) \
        CHECK_NULL_ARG__INTERNAL(ARG3) \
        CHECK_NULL_ARG__INTERNAL(ARG4) \
    } while(0)

/**
 * Memory allocation check macro with return
 */
#define CHECK_NULL_NOMEM_RETURN(ARG) \
    do { \
        if (NULL == ARG) { \
            DPRINT("Unable to allocate memory in %s", __func__); \
            return ERR_NOMEM; \
        } \
    } while(0)

/**
 * Memory allocation check macro with setting error
 */
#define CHECK_NULL_NOMEM_ERROR(ARG, ERROR) \
    do { \
        if (NULL == ARG) { \
            DPRINT("Unable to allocate memory in %s", __func__); \
            ERROR = ERR_NOMEM; \
        } \
    } while(0)

/**
 * Memory allocation check macro with goto
 */
#define CHECK_NULL_NOMEM_GOTO(ARG, ERROR, LABEL) \
    do { \
        if (NULL == ARG) { \
            DPRINT("Unable to allocate memory in %s", __func__); \
            ERROR = ERR_NOMEM; \
            goto LABEL; \
        } \
    } while(0)


/**
 * Return code check macro with return and no variable arguments.
 */
#define CHECK_RC_MSG_RETURN(RC, MSG) \
    do { \
        if (SR_ERR_OK != RC) { \
            DPRINT_MSG(MSG); \
            return RC; \
        } \
    } while(0)

/**
 * Return code check macro with return and variable arguments.
 */
#define CHECK_RC_LOG_RETURN(RC, MSG, ...) \
    do { \
        if (SR_ERR_OK != RC) { \
            DPRINT(MSG, __VA_ARGS__); \
            return RC; \
        } \
    } while(0)

/**
 * Return code check macro with goto and no variable arguments.
 */
#define CHECK_RC_MSG_GOTO(RC, LABEL, MSG) \
    do { \
        if (SR_ERR_OK != RC) { \
            DPRINT_MSG(MSG); \
            goto LABEL; \
        } \
    } while(0)

/**
 * Return code check macro with goto and variable arguments.
 */
#define CHECK_RC_LOG_GOTO(RC, LABEL, MSG, ...) \
    do { \
        if (SR_ERR_OK != RC) { \
            DPRINT(MSG, __VA_ARGS__); \
            goto LABEL; \
        } \
    } while(0)


/**
 * Non-zero value check macro with return and no variable arguments.
 */
#define CHECK_ZERO_MSG_RETURN(RET, ERROR, MSG) \
    do { \
        if (0 != RET) { \
            DPRINT_MSG(MSG); \
            return ERROR; \
        } \
    } while(0)

/**
 * Non-zero value check macro with return and variable arguments.
 */
#define CHECK_ZERO_LOG_RETURN(RET, ERROR, MSG, ...) \
    do { \
        if (0 != RET) { \
            DPRINT(MSG, __VA_ARGS__); \
            return ERROR; \
        } \
    } while(0)

/**
 * Non-zero value check macro with goto and no variable arguments.
 */
#define CHECK_ZERO_MSG_GOTO(RET, RC, ERROR, LABEL, MSG) \
    do { \
        if (0 != RET) { \
            DPRINT_MSG(MSG); \
            RC = ERROR; \
            goto LABEL; \
        } \
    } while(0)

/**
 * Non-zero value check macro with goto and variable arguments.
 */
#define CHECK_ZERO_LOG_GOTO(RET, RC, ERROR, LABEL, MSG, ...) \
    do { \
        if (0 != RET) { \
            DPRINT(MSG, __VA_ARGS__); \
            RC = ERROR; \
            goto LABEL; \
        } \
    } while(0)

/**
 * Non-minus value check macro with return and no variable arguments.
 */
#define CHECK_NOT_MINUS1_MSG_RETURN(RET, ERROR, MSG) \
    do { \
        if (-1 == RET) { \
            DPRINT_MSG(MSG); \
            return ERROR; \
        } \
    } while(0)

/**
 * Non-minus value check macro with return and variable arguments.
 */
#define CHECK_NOT_MINUS1_LOG_RETURN(RET, ERROR, MSG, ...) \
    do { \
        if (-1 == RET) { \
            DPRINT(MSG, __VA_ARGS__); \
            return ERROR; \
        } \
    } while(0)

/**
 * Non-minus value check macro with goto and no variable arguments.
 */
#define CHECK_NOT_MINUS1_MSG_GOTO(RET, RC, ERROR, LABEL, MSG) \
    do { \
        if (-1 == RET) { \
            DPRINT_MSG(MSG); \
            RC = ERROR; \
            goto LABEL; \
        } \
    } while(0)

/**
 * Non-minus value check macro with goto and variable arguments.
 */
#define CHECK_NOT_MINUS1_LOG_GOTO(RET, RC, ERROR, LABEL, MSG, ...) \
    do { \
        if (-1 == RET) { \
            DPRINT(MSG, __VA_ARGS__); \
            RC = ERROR; \
            goto LABEL; \
        } \
    } while(0)

/**
 * NULL value checker - returns given error code.
 */
#define CHECK_NULL_RETURN(ARG, RC) \
    if (NULL == ARG) { \
        DPRINT("NULL value detected for %s in %s", #ARG, __func__); \
        return RC; \
    } \




