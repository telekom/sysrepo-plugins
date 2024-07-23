#include "core/nftables.hpp"
#include "nftables.hpp"


NFTables::NFTables()
{   
    m_ctx = NULL;
    m_ctx = nft_ctx_new(0);
    if(!m_ctx){
        throw std::bad_alloc();
    }
    // Default settings, 
    nft_ctx_output_set_flags(m_ctx, NFT_CTX_OUTPUT_HANDLE | NFT_CTX_OUTPUT_JSON);

}

std::string NFTables::dumpJSON()
{
    int err = 0;
    err = nft_run_cmd_from_buffer(m_ctx, "list ruleset");
    if(err < 0)
        throw NFTablesCommandExecException("Failed to exec command list ruleset!");

    std::string buffer(nft_ctx_get_output_buffer(m_ctx));
    return buffer;
}





NFTables::~NFTables()
{
    nft_ctx_free(m_ctx);
}
