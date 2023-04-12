
// Generated from ./Cypher.g4 by ANTLR 4.7.2


#include "CypherListener.h"
#include "CypherVisitor.h"

#include "CypherParser.h"


using namespace antlrcpp;
using namespace antlr4;

CypherParser::CypherParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CypherParser::~CypherParser() {
  delete _interpreter;
}

std::string CypherParser::getGrammarFileName() const {
  return "Cypher.g4";
}

const std::vector<std::string>& CypherParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CypherParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- OC_CypherContext ------------------------------------------------------------------

CypherParser::OC_CypherContext::OC_CypherContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_StatementContext* CypherParser::OC_CypherContext::oC_Statement() {
  return getRuleContext<CypherParser::OC_StatementContext>(0);
}

tree::TerminalNode* CypherParser::OC_CypherContext::EOF() {
  return getToken(CypherParser::EOF, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_CypherContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_CypherContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_CypherContext::getRuleIndex() const {
  return CypherParser::RuleOC_Cypher;
}

void CypherParser::OC_CypherContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Cypher(this);
}

void CypherParser::OC_CypherContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Cypher(this);
}


antlrcpp::Any CypherParser::OC_CypherContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Cypher(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_CypherContext* CypherParser::oC_Cypher() {
  OC_CypherContext *_localctx = _tracker.createInstance<OC_CypherContext>(_ctx, getState());
  enterRule(_localctx, 0, CypherParser::RuleOC_Cypher);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(209);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(208);
      match(CypherParser::SP);
    }
    setState(211);
    oC_Statement();
    setState(216);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
    case 1: {
      setState(213);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(212);
        match(CypherParser::SP);
      }
      setState(215);
      match(CypherParser::T__0);
      break;
    }

    }
    setState(219);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(218);
      match(CypherParser::SP);
    }
    setState(221);
    match(CypherParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_StatementContext ------------------------------------------------------------------

CypherParser::OC_StatementContext::OC_StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_QueryContext* CypherParser::OC_StatementContext::oC_Query() {
  return getRuleContext<CypherParser::OC_QueryContext>(0);
}


size_t CypherParser::OC_StatementContext::getRuleIndex() const {
  return CypherParser::RuleOC_Statement;
}

void CypherParser::OC_StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Statement(this);
}

void CypherParser::OC_StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Statement(this);
}


antlrcpp::Any CypherParser::OC_StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Statement(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_StatementContext* CypherParser::oC_Statement() {
  OC_StatementContext *_localctx = _tracker.createInstance<OC_StatementContext>(_ctx, getState());
  enterRule(_localctx, 2, CypherParser::RuleOC_Statement);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(223);
    oC_Query();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_QueryContext ------------------------------------------------------------------

CypherParser::OC_QueryContext::OC_QueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_RegularQueryContext* CypherParser::OC_QueryContext::oC_RegularQuery() {
  return getRuleContext<CypherParser::OC_RegularQueryContext>(0);
}

CypherParser::OC_StandaloneCallContext* CypherParser::OC_QueryContext::oC_StandaloneCall() {
  return getRuleContext<CypherParser::OC_StandaloneCallContext>(0);
}


size_t CypherParser::OC_QueryContext::getRuleIndex() const {
  return CypherParser::RuleOC_Query;
}

void CypherParser::OC_QueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Query(this);
}

void CypherParser::OC_QueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Query(this);
}


antlrcpp::Any CypherParser::OC_QueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Query(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_QueryContext* CypherParser::oC_Query() {
  OC_QueryContext *_localctx = _tracker.createInstance<OC_QueryContext>(_ctx, getState());
  enterRule(_localctx, 4, CypherParser::RuleOC_Query);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(227);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(225);
      oC_RegularQuery();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(226);
      oC_StandaloneCall();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RegularQueryContext ------------------------------------------------------------------

CypherParser::OC_RegularQueryContext::OC_RegularQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SingleQueryContext* CypherParser::OC_RegularQueryContext::oC_SingleQuery() {
  return getRuleContext<CypherParser::OC_SingleQueryContext>(0);
}

std::vector<CypherParser::OC_UnionContext *> CypherParser::OC_RegularQueryContext::oC_Union() {
  return getRuleContexts<CypherParser::OC_UnionContext>();
}

CypherParser::OC_UnionContext* CypherParser::OC_RegularQueryContext::oC_Union(size_t i) {
  return getRuleContext<CypherParser::OC_UnionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_RegularQueryContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RegularQueryContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_RegularQueryContext::getRuleIndex() const {
  return CypherParser::RuleOC_RegularQuery;
}

void CypherParser::OC_RegularQueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RegularQuery(this);
}

void CypherParser::OC_RegularQueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RegularQuery(this);
}


antlrcpp::Any CypherParser::OC_RegularQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RegularQuery(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RegularQueryContext* CypherParser::oC_RegularQuery() {
  OC_RegularQueryContext *_localctx = _tracker.createInstance<OC_RegularQueryContext>(_ctx, getState());
  enterRule(_localctx, 6, CypherParser::RuleOC_RegularQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(229);
    oC_SingleQuery();
    setState(236);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(231);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(230);
          match(CypherParser::SP);
        }
        setState(233);
        oC_Union(); 
      }
      setState(238);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_UnionContext ------------------------------------------------------------------

CypherParser::OC_UnionContext::OC_UnionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_UnionContext::UNION() {
  return getToken(CypherParser::UNION, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_UnionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_UnionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_UnionContext::ALL() {
  return getToken(CypherParser::ALL, 0);
}

CypherParser::OC_SingleQueryContext* CypherParser::OC_UnionContext::oC_SingleQuery() {
  return getRuleContext<CypherParser::OC_SingleQueryContext>(0);
}


size_t CypherParser::OC_UnionContext::getRuleIndex() const {
  return CypherParser::RuleOC_Union;
}

void CypherParser::OC_UnionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Union(this);
}

void CypherParser::OC_UnionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Union(this);
}


antlrcpp::Any CypherParser::OC_UnionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Union(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_UnionContext* CypherParser::oC_Union() {
  OC_UnionContext *_localctx = _tracker.createInstance<OC_UnionContext>(_ctx, getState());
  enterRule(_localctx, 8, CypherParser::RuleOC_Union);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(251);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(239);
      match(CypherParser::UNION);
      setState(240);
      match(CypherParser::SP);
      setState(241);
      match(CypherParser::ALL);
      setState(243);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(242);
        match(CypherParser::SP);
      }
      setState(245);
      oC_SingleQuery();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(246);
      match(CypherParser::UNION);
      setState(248);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(247);
        match(CypherParser::SP);
      }
      setState(250);
      oC_SingleQuery();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SingleQueryContext ------------------------------------------------------------------

CypherParser::OC_SingleQueryContext::OC_SingleQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SinglePartQueryContext* CypherParser::OC_SingleQueryContext::oC_SinglePartQuery() {
  return getRuleContext<CypherParser::OC_SinglePartQueryContext>(0);
}

CypherParser::OC_MultiPartQueryContext* CypherParser::OC_SingleQueryContext::oC_MultiPartQuery() {
  return getRuleContext<CypherParser::OC_MultiPartQueryContext>(0);
}


size_t CypherParser::OC_SingleQueryContext::getRuleIndex() const {
  return CypherParser::RuleOC_SingleQuery;
}

void CypherParser::OC_SingleQueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_SingleQuery(this);
}

void CypherParser::OC_SingleQueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_SingleQuery(this);
}


antlrcpp::Any CypherParser::OC_SingleQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_SingleQuery(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SingleQueryContext* CypherParser::oC_SingleQuery() {
  OC_SingleQueryContext *_localctx = _tracker.createInstance<OC_SingleQueryContext>(_ctx, getState());
  enterRule(_localctx, 10, CypherParser::RuleOC_SingleQuery);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(255);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(253);
      oC_SinglePartQuery();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(254);
      oC_MultiPartQuery();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SinglePartQueryContext ------------------------------------------------------------------

CypherParser::OC_SinglePartQueryContext::OC_SinglePartQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ReturnContext* CypherParser::OC_SinglePartQueryContext::oC_Return() {
  return getRuleContext<CypherParser::OC_ReturnContext>(0);
}

std::vector<CypherParser::OC_ReadingClauseContext *> CypherParser::OC_SinglePartQueryContext::oC_ReadingClause() {
  return getRuleContexts<CypherParser::OC_ReadingClauseContext>();
}

CypherParser::OC_ReadingClauseContext* CypherParser::OC_SinglePartQueryContext::oC_ReadingClause(size_t i) {
  return getRuleContext<CypherParser::OC_ReadingClauseContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_SinglePartQueryContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_SinglePartQueryContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_UpdatingClauseContext *> CypherParser::OC_SinglePartQueryContext::oC_UpdatingClause() {
  return getRuleContexts<CypherParser::OC_UpdatingClauseContext>();
}

CypherParser::OC_UpdatingClauseContext* CypherParser::OC_SinglePartQueryContext::oC_UpdatingClause(size_t i) {
  return getRuleContext<CypherParser::OC_UpdatingClauseContext>(i);
}


size_t CypherParser::OC_SinglePartQueryContext::getRuleIndex() const {
  return CypherParser::RuleOC_SinglePartQuery;
}

void CypherParser::OC_SinglePartQueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_SinglePartQuery(this);
}

void CypherParser::OC_SinglePartQueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_SinglePartQuery(this);
}


antlrcpp::Any CypherParser::OC_SinglePartQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_SinglePartQuery(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SinglePartQueryContext* CypherParser::oC_SinglePartQuery() {
  OC_SinglePartQueryContext *_localctx = _tracker.createInstance<OC_SinglePartQueryContext>(_ctx, getState());
  enterRule(_localctx, 12, CypherParser::RuleOC_SinglePartQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(292);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(263);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CypherParser::OPTIONAL)
        | (1ULL << CypherParser::MATCH)
        | (1ULL << CypherParser::UNWIND)
        | (1ULL << CypherParser::CALL))) != 0)) {
        setState(257);
        oC_ReadingClause();
        setState(259);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(258);
          match(CypherParser::SP);
        }
        setState(265);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(266);
      oC_Return();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(273);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CypherParser::OPTIONAL)
        | (1ULL << CypherParser::MATCH)
        | (1ULL << CypherParser::UNWIND)
        | (1ULL << CypherParser::CALL))) != 0)) {
        setState(267);
        oC_ReadingClause();
        setState(269);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(268);
          match(CypherParser::SP);
        }
        setState(275);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
      setState(276);
      oC_UpdatingClause();
      setState(283);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(278);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(277);
            match(CypherParser::SP);
          }
          setState(280);
          oC_UpdatingClause(); 
        }
        setState(285);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
      }
      setState(290);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 18, _ctx)) {
      case 1: {
        setState(287);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(286);
          match(CypherParser::SP);
        }
        setState(289);
        oC_Return();
        break;
      }

      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_MultiPartQueryContext ------------------------------------------------------------------

CypherParser::OC_MultiPartQueryContext::OC_MultiPartQueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SinglePartQueryContext* CypherParser::OC_MultiPartQueryContext::oC_SinglePartQuery() {
  return getRuleContext<CypherParser::OC_SinglePartQueryContext>(0);
}

std::vector<CypherParser::OC_WithContext *> CypherParser::OC_MultiPartQueryContext::oC_With() {
  return getRuleContexts<CypherParser::OC_WithContext>();
}

CypherParser::OC_WithContext* CypherParser::OC_MultiPartQueryContext::oC_With(size_t i) {
  return getRuleContext<CypherParser::OC_WithContext>(i);
}

std::vector<CypherParser::OC_ReadingClauseContext *> CypherParser::OC_MultiPartQueryContext::oC_ReadingClause() {
  return getRuleContexts<CypherParser::OC_ReadingClauseContext>();
}

CypherParser::OC_ReadingClauseContext* CypherParser::OC_MultiPartQueryContext::oC_ReadingClause(size_t i) {
  return getRuleContext<CypherParser::OC_ReadingClauseContext>(i);
}

std::vector<CypherParser::OC_UpdatingClauseContext *> CypherParser::OC_MultiPartQueryContext::oC_UpdatingClause() {
  return getRuleContexts<CypherParser::OC_UpdatingClauseContext>();
}

CypherParser::OC_UpdatingClauseContext* CypherParser::OC_MultiPartQueryContext::oC_UpdatingClause(size_t i) {
  return getRuleContext<CypherParser::OC_UpdatingClauseContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_MultiPartQueryContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_MultiPartQueryContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_MultiPartQueryContext::getRuleIndex() const {
  return CypherParser::RuleOC_MultiPartQuery;
}

void CypherParser::OC_MultiPartQueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_MultiPartQuery(this);
}

void CypherParser::OC_MultiPartQueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_MultiPartQuery(this);
}


antlrcpp::Any CypherParser::OC_MultiPartQueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_MultiPartQuery(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_MultiPartQueryContext* CypherParser::oC_MultiPartQuery() {
  OC_MultiPartQueryContext *_localctx = _tracker.createInstance<OC_MultiPartQueryContext>(_ctx, getState());
  enterRule(_localctx, 14, CypherParser::RuleOC_MultiPartQuery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(316); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(300);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while ((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << CypherParser::OPTIONAL)
                | (1ULL << CypherParser::MATCH)
                | (1ULL << CypherParser::UNWIND)
                | (1ULL << CypherParser::CALL))) != 0)) {
                setState(294);
                oC_ReadingClause();
                setState(296);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == CypherParser::SP) {
                  setState(295);
                  match(CypherParser::SP);
                }
                setState(302);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
              setState(309);
              _errHandler->sync(this);
              _la = _input->LA(1);
              while ((((_la & ~ 0x3fULL) == 0) &&
                ((1ULL << _la) & ((1ULL << CypherParser::MERGE)
                | (1ULL << CypherParser::CREATE)
                | (1ULL << CypherParser::SET)
                | (1ULL << CypherParser::DETACH)
                | (1ULL << CypherParser::DELETE)
                | (1ULL << CypherParser::REMOVE))) != 0)) {
                setState(303);
                oC_UpdatingClause();
                setState(305);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == CypherParser::SP) {
                  setState(304);
                  match(CypherParser::SP);
                }
                setState(311);
                _errHandler->sync(this);
                _la = _input->LA(1);
              }
              setState(312);
              oC_With();
              setState(314);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == CypherParser::SP) {
                setState(313);
                match(CypherParser::SP);
              }
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(318); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 25, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
    setState(320);
    oC_SinglePartQuery();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_UpdatingClauseContext ------------------------------------------------------------------

CypherParser::OC_UpdatingClauseContext::OC_UpdatingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_CreateContext* CypherParser::OC_UpdatingClauseContext::oC_Create() {
  return getRuleContext<CypherParser::OC_CreateContext>(0);
}

CypherParser::OC_MergeContext* CypherParser::OC_UpdatingClauseContext::oC_Merge() {
  return getRuleContext<CypherParser::OC_MergeContext>(0);
}

CypherParser::OC_DeleteContext* CypherParser::OC_UpdatingClauseContext::oC_Delete() {
  return getRuleContext<CypherParser::OC_DeleteContext>(0);
}

CypherParser::OC_SetContext* CypherParser::OC_UpdatingClauseContext::oC_Set() {
  return getRuleContext<CypherParser::OC_SetContext>(0);
}

CypherParser::OC_RemoveContext* CypherParser::OC_UpdatingClauseContext::oC_Remove() {
  return getRuleContext<CypherParser::OC_RemoveContext>(0);
}


size_t CypherParser::OC_UpdatingClauseContext::getRuleIndex() const {
  return CypherParser::RuleOC_UpdatingClause;
}

void CypherParser::OC_UpdatingClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_UpdatingClause(this);
}

void CypherParser::OC_UpdatingClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_UpdatingClause(this);
}


antlrcpp::Any CypherParser::OC_UpdatingClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_UpdatingClause(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_UpdatingClauseContext* CypherParser::oC_UpdatingClause() {
  OC_UpdatingClauseContext *_localctx = _tracker.createInstance<OC_UpdatingClauseContext>(_ctx, getState());
  enterRule(_localctx, 16, CypherParser::RuleOC_UpdatingClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(327);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::CREATE: {
        enterOuterAlt(_localctx, 1);
        setState(322);
        oC_Create();
        break;
      }

      case CypherParser::MERGE: {
        enterOuterAlt(_localctx, 2);
        setState(323);
        oC_Merge();
        break;
      }

      case CypherParser::DETACH:
      case CypherParser::DELETE: {
        enterOuterAlt(_localctx, 3);
        setState(324);
        oC_Delete();
        break;
      }

      case CypherParser::SET: {
        enterOuterAlt(_localctx, 4);
        setState(325);
        oC_Set();
        break;
      }

      case CypherParser::REMOVE: {
        enterOuterAlt(_localctx, 5);
        setState(326);
        oC_Remove();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ReadingClauseContext ------------------------------------------------------------------

CypherParser::OC_ReadingClauseContext::OC_ReadingClauseContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_MatchContext* CypherParser::OC_ReadingClauseContext::oC_Match() {
  return getRuleContext<CypherParser::OC_MatchContext>(0);
}

CypherParser::OC_UnwindContext* CypherParser::OC_ReadingClauseContext::oC_Unwind() {
  return getRuleContext<CypherParser::OC_UnwindContext>(0);
}

CypherParser::OC_InQueryCallContext* CypherParser::OC_ReadingClauseContext::oC_InQueryCall() {
  return getRuleContext<CypherParser::OC_InQueryCallContext>(0);
}


size_t CypherParser::OC_ReadingClauseContext::getRuleIndex() const {
  return CypherParser::RuleOC_ReadingClause;
}

void CypherParser::OC_ReadingClauseContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ReadingClause(this);
}

void CypherParser::OC_ReadingClauseContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ReadingClause(this);
}


antlrcpp::Any CypherParser::OC_ReadingClauseContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ReadingClause(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ReadingClauseContext* CypherParser::oC_ReadingClause() {
  OC_ReadingClauseContext *_localctx = _tracker.createInstance<OC_ReadingClauseContext>(_ctx, getState());
  enterRule(_localctx, 18, CypherParser::RuleOC_ReadingClause);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(332);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::OPTIONAL:
      case CypherParser::MATCH: {
        enterOuterAlt(_localctx, 1);
        setState(329);
        oC_Match();
        break;
      }

      case CypherParser::UNWIND: {
        enterOuterAlt(_localctx, 2);
        setState(330);
        oC_Unwind();
        break;
      }

      case CypherParser::CALL: {
        enterOuterAlt(_localctx, 3);
        setState(331);
        oC_InQueryCall();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_MatchContext ------------------------------------------------------------------

CypherParser::OC_MatchContext::OC_MatchContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_MatchContext::MATCH() {
  return getToken(CypherParser::MATCH, 0);
}

CypherParser::OC_PatternContext* CypherParser::OC_MatchContext::oC_Pattern() {
  return getRuleContext<CypherParser::OC_PatternContext>(0);
}

tree::TerminalNode* CypherParser::OC_MatchContext::OPTIONAL() {
  return getToken(CypherParser::OPTIONAL, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_MatchContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_MatchContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_WhereContext* CypherParser::OC_MatchContext::oC_Where() {
  return getRuleContext<CypherParser::OC_WhereContext>(0);
}


size_t CypherParser::OC_MatchContext::getRuleIndex() const {
  return CypherParser::RuleOC_Match;
}

void CypherParser::OC_MatchContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Match(this);
}

void CypherParser::OC_MatchContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Match(this);
}


antlrcpp::Any CypherParser::OC_MatchContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Match(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_MatchContext* CypherParser::oC_Match() {
  OC_MatchContext *_localctx = _tracker.createInstance<OC_MatchContext>(_ctx, getState());
  enterRule(_localctx, 20, CypherParser::RuleOC_Match);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(336);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::OPTIONAL) {
      setState(334);
      match(CypherParser::OPTIONAL);
      setState(335);
      match(CypherParser::SP);
    }
    setState(338);
    match(CypherParser::MATCH);
    setState(340);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(339);
      match(CypherParser::SP);
    }
    setState(342);
    oC_Pattern();
    setState(347);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 31, _ctx)) {
    case 1: {
      setState(344);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(343);
        match(CypherParser::SP);
      }
      setState(346);
      oC_Where();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_UnwindContext ------------------------------------------------------------------

CypherParser::OC_UnwindContext::OC_UnwindContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_UnwindContext::UNWIND() {
  return getToken(CypherParser::UNWIND, 0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_UnwindContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_UnwindContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_UnwindContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_UnwindContext::AS() {
  return getToken(CypherParser::AS, 0);
}

CypherParser::OC_VariableContext* CypherParser::OC_UnwindContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}


size_t CypherParser::OC_UnwindContext::getRuleIndex() const {
  return CypherParser::RuleOC_Unwind;
}

void CypherParser::OC_UnwindContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Unwind(this);
}

void CypherParser::OC_UnwindContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Unwind(this);
}


antlrcpp::Any CypherParser::OC_UnwindContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Unwind(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_UnwindContext* CypherParser::oC_Unwind() {
  OC_UnwindContext *_localctx = _tracker.createInstance<OC_UnwindContext>(_ctx, getState());
  enterRule(_localctx, 22, CypherParser::RuleOC_Unwind);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(349);
    match(CypherParser::UNWIND);
    setState(351);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(350);
      match(CypherParser::SP);
    }
    setState(353);
    oC_Expression();
    setState(354);
    match(CypherParser::SP);
    setState(355);
    match(CypherParser::AS);
    setState(356);
    match(CypherParser::SP);
    setState(357);
    oC_Variable();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_MergeContext ------------------------------------------------------------------

CypherParser::OC_MergeContext::OC_MergeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_MergeContext::MERGE() {
  return getToken(CypherParser::MERGE, 0);
}

CypherParser::OC_PatternPartContext* CypherParser::OC_MergeContext::oC_PatternPart() {
  return getRuleContext<CypherParser::OC_PatternPartContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_MergeContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_MergeContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_MergeActionContext *> CypherParser::OC_MergeContext::oC_MergeAction() {
  return getRuleContexts<CypherParser::OC_MergeActionContext>();
}

CypherParser::OC_MergeActionContext* CypherParser::OC_MergeContext::oC_MergeAction(size_t i) {
  return getRuleContext<CypherParser::OC_MergeActionContext>(i);
}


size_t CypherParser::OC_MergeContext::getRuleIndex() const {
  return CypherParser::RuleOC_Merge;
}

void CypherParser::OC_MergeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Merge(this);
}

void CypherParser::OC_MergeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Merge(this);
}


antlrcpp::Any CypherParser::OC_MergeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Merge(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_MergeContext* CypherParser::oC_Merge() {
  OC_MergeContext *_localctx = _tracker.createInstance<OC_MergeContext>(_ctx, getState());
  enterRule(_localctx, 24, CypherParser::RuleOC_Merge);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(359);
    match(CypherParser::MERGE);
    setState(361);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(360);
      match(CypherParser::SP);
    }
    setState(363);
    oC_PatternPart();
    setState(368);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(364);
        match(CypherParser::SP);
        setState(365);
        oC_MergeAction(); 
      }
      setState(370);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 34, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_MergeActionContext ------------------------------------------------------------------

CypherParser::OC_MergeActionContext::OC_MergeActionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_MergeActionContext::ON() {
  return getToken(CypherParser::ON, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_MergeActionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_MergeActionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_MergeActionContext::MATCH() {
  return getToken(CypherParser::MATCH, 0);
}

CypherParser::OC_SetContext* CypherParser::OC_MergeActionContext::oC_Set() {
  return getRuleContext<CypherParser::OC_SetContext>(0);
}

tree::TerminalNode* CypherParser::OC_MergeActionContext::CREATE() {
  return getToken(CypherParser::CREATE, 0);
}


size_t CypherParser::OC_MergeActionContext::getRuleIndex() const {
  return CypherParser::RuleOC_MergeAction;
}

void CypherParser::OC_MergeActionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_MergeAction(this);
}

void CypherParser::OC_MergeActionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_MergeAction(this);
}


antlrcpp::Any CypherParser::OC_MergeActionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_MergeAction(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_MergeActionContext* CypherParser::oC_MergeAction() {
  OC_MergeActionContext *_localctx = _tracker.createInstance<OC_MergeActionContext>(_ctx, getState());
  enterRule(_localctx, 26, CypherParser::RuleOC_MergeAction);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(381);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 35, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(371);
      match(CypherParser::ON);
      setState(372);
      match(CypherParser::SP);
      setState(373);
      match(CypherParser::MATCH);
      setState(374);
      match(CypherParser::SP);
      setState(375);
      oC_Set();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(376);
      match(CypherParser::ON);
      setState(377);
      match(CypherParser::SP);
      setState(378);
      match(CypherParser::CREATE);
      setState(379);
      match(CypherParser::SP);
      setState(380);
      oC_Set();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_CreateContext ------------------------------------------------------------------

CypherParser::OC_CreateContext::OC_CreateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_CreateContext::CREATE() {
  return getToken(CypherParser::CREATE, 0);
}

CypherParser::OC_PatternContext* CypherParser::OC_CreateContext::oC_Pattern() {
  return getRuleContext<CypherParser::OC_PatternContext>(0);
}

tree::TerminalNode* CypherParser::OC_CreateContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_CreateContext::getRuleIndex() const {
  return CypherParser::RuleOC_Create;
}

void CypherParser::OC_CreateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Create(this);
}

void CypherParser::OC_CreateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Create(this);
}


antlrcpp::Any CypherParser::OC_CreateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Create(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_CreateContext* CypherParser::oC_Create() {
  OC_CreateContext *_localctx = _tracker.createInstance<OC_CreateContext>(_ctx, getState());
  enterRule(_localctx, 28, CypherParser::RuleOC_Create);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(383);
    match(CypherParser::CREATE);
    setState(385);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(384);
      match(CypherParser::SP);
    }
    setState(387);
    oC_Pattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SetContext ------------------------------------------------------------------

CypherParser::OC_SetContext::OC_SetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_SetContext::SET() {
  return getToken(CypherParser::SET, 0);
}

std::vector<CypherParser::OC_SetItemContext *> CypherParser::OC_SetContext::oC_SetItem() {
  return getRuleContexts<CypherParser::OC_SetItemContext>();
}

CypherParser::OC_SetItemContext* CypherParser::OC_SetContext::oC_SetItem(size_t i) {
  return getRuleContext<CypherParser::OC_SetItemContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_SetContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_SetContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_SetContext::getRuleIndex() const {
  return CypherParser::RuleOC_Set;
}

void CypherParser::OC_SetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Set(this);
}

void CypherParser::OC_SetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Set(this);
}


antlrcpp::Any CypherParser::OC_SetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Set(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SetContext* CypherParser::oC_Set() {
  OC_SetContext *_localctx = _tracker.createInstance<OC_SetContext>(_ctx, getState());
  enterRule(_localctx, 30, CypherParser::RuleOC_Set);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(389);
    match(CypherParser::SET);
    setState(391);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(390);
      match(CypherParser::SP);
    }
    setState(393);
    oC_SetItem();
    setState(404);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(395);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(394);
          match(CypherParser::SP);
        }
        setState(397);
        match(CypherParser::T__1);
        setState(399);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(398);
          match(CypherParser::SP);
        }
        setState(401);
        oC_SetItem(); 
      }
      setState(406);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 40, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SetItemContext ------------------------------------------------------------------

CypherParser::OC_SetItemContext::OC_SetItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_PropertyExpressionContext* CypherParser::OC_SetItemContext::oC_PropertyExpression() {
  return getRuleContext<CypherParser::OC_PropertyExpressionContext>(0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_SetItemContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_SetItemContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_SetItemContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_VariableContext* CypherParser::OC_SetItemContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_NodeLabelsContext* CypherParser::OC_SetItemContext::oC_NodeLabels() {
  return getRuleContext<CypherParser::OC_NodeLabelsContext>(0);
}


size_t CypherParser::OC_SetItemContext::getRuleIndex() const {
  return CypherParser::RuleOC_SetItem;
}

void CypherParser::OC_SetItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_SetItem(this);
}

void CypherParser::OC_SetItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_SetItem(this);
}


antlrcpp::Any CypherParser::OC_SetItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_SetItem(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SetItemContext* CypherParser::oC_SetItem() {
  OC_SetItemContext *_localctx = _tracker.createInstance<OC_SetItemContext>(_ctx, getState());
  enterRule(_localctx, 32, CypherParser::RuleOC_SetItem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(443);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 48, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(407);
      oC_PropertyExpression();
      setState(409);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(408);
        match(CypherParser::SP);
      }
      setState(411);
      match(CypherParser::T__2);
      setState(413);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(412);
        match(CypherParser::SP);
      }
      setState(415);
      oC_Expression();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(417);
      oC_Variable();
      setState(419);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(418);
        match(CypherParser::SP);
      }
      setState(421);
      match(CypherParser::T__2);
      setState(423);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(422);
        match(CypherParser::SP);
      }
      setState(425);
      oC_Expression();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(427);
      oC_Variable();
      setState(429);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(428);
        match(CypherParser::SP);
      }
      setState(431);
      match(CypherParser::T__3);
      setState(433);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(432);
        match(CypherParser::SP);
      }
      setState(435);
      oC_Expression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(437);
      oC_Variable();
      setState(439);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(438);
        match(CypherParser::SP);
      }
      setState(441);
      oC_NodeLabels();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_DeleteContext ------------------------------------------------------------------

CypherParser::OC_DeleteContext::OC_DeleteContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_DeleteContext::DELETE() {
  return getToken(CypherParser::DELETE, 0);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_DeleteContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_DeleteContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}

tree::TerminalNode* CypherParser::OC_DeleteContext::DETACH() {
  return getToken(CypherParser::DETACH, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_DeleteContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_DeleteContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_DeleteContext::getRuleIndex() const {
  return CypherParser::RuleOC_Delete;
}

void CypherParser::OC_DeleteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Delete(this);
}

void CypherParser::OC_DeleteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Delete(this);
}


antlrcpp::Any CypherParser::OC_DeleteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Delete(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_DeleteContext* CypherParser::oC_Delete() {
  OC_DeleteContext *_localctx = _tracker.createInstance<OC_DeleteContext>(_ctx, getState());
  enterRule(_localctx, 34, CypherParser::RuleOC_Delete);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(447);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::DETACH) {
      setState(445);
      match(CypherParser::DETACH);
      setState(446);
      match(CypherParser::SP);
    }
    setState(449);
    match(CypherParser::DELETE);
    setState(451);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(450);
      match(CypherParser::SP);
    }
    setState(453);
    oC_Expression();
    setState(464);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(455);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(454);
          match(CypherParser::SP);
        }
        setState(457);
        match(CypherParser::T__1);
        setState(459);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(458);
          match(CypherParser::SP);
        }
        setState(461);
        oC_Expression(); 
      }
      setState(466);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 53, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RemoveContext ------------------------------------------------------------------

CypherParser::OC_RemoveContext::OC_RemoveContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_RemoveContext::REMOVE() {
  return getToken(CypherParser::REMOVE, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_RemoveContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RemoveContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_RemoveItemContext *> CypherParser::OC_RemoveContext::oC_RemoveItem() {
  return getRuleContexts<CypherParser::OC_RemoveItemContext>();
}

CypherParser::OC_RemoveItemContext* CypherParser::OC_RemoveContext::oC_RemoveItem(size_t i) {
  return getRuleContext<CypherParser::OC_RemoveItemContext>(i);
}


size_t CypherParser::OC_RemoveContext::getRuleIndex() const {
  return CypherParser::RuleOC_Remove;
}

void CypherParser::OC_RemoveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Remove(this);
}

void CypherParser::OC_RemoveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Remove(this);
}


antlrcpp::Any CypherParser::OC_RemoveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Remove(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RemoveContext* CypherParser::oC_Remove() {
  OC_RemoveContext *_localctx = _tracker.createInstance<OC_RemoveContext>(_ctx, getState());
  enterRule(_localctx, 36, CypherParser::RuleOC_Remove);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(467);
    match(CypherParser::REMOVE);
    setState(468);
    match(CypherParser::SP);
    setState(469);
    oC_RemoveItem();
    setState(480);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(471);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(470);
          match(CypherParser::SP);
        }
        setState(473);
        match(CypherParser::T__1);
        setState(475);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(474);
          match(CypherParser::SP);
        }
        setState(477);
        oC_RemoveItem(); 
      }
      setState(482);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 56, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RemoveItemContext ------------------------------------------------------------------

CypherParser::OC_RemoveItemContext::OC_RemoveItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_VariableContext* CypherParser::OC_RemoveItemContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_NodeLabelsContext* CypherParser::OC_RemoveItemContext::oC_NodeLabels() {
  return getRuleContext<CypherParser::OC_NodeLabelsContext>(0);
}

CypherParser::OC_PropertyExpressionContext* CypherParser::OC_RemoveItemContext::oC_PropertyExpression() {
  return getRuleContext<CypherParser::OC_PropertyExpressionContext>(0);
}


size_t CypherParser::OC_RemoveItemContext::getRuleIndex() const {
  return CypherParser::RuleOC_RemoveItem;
}

void CypherParser::OC_RemoveItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RemoveItem(this);
}

void CypherParser::OC_RemoveItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RemoveItem(this);
}


antlrcpp::Any CypherParser::OC_RemoveItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RemoveItem(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RemoveItemContext* CypherParser::oC_RemoveItem() {
  OC_RemoveItemContext *_localctx = _tracker.createInstance<OC_RemoveItemContext>(_ctx, getState());
  enterRule(_localctx, 38, CypherParser::RuleOC_RemoveItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(487);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 57, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(483);
      oC_Variable();
      setState(484);
      oC_NodeLabels();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(486);
      oC_PropertyExpression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_InQueryCallContext ------------------------------------------------------------------

CypherParser::OC_InQueryCallContext::OC_InQueryCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_InQueryCallContext::CALL() {
  return getToken(CypherParser::CALL, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_InQueryCallContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_InQueryCallContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_ExplicitProcedureInvocationContext* CypherParser::OC_InQueryCallContext::oC_ExplicitProcedureInvocation() {
  return getRuleContext<CypherParser::OC_ExplicitProcedureInvocationContext>(0);
}

tree::TerminalNode* CypherParser::OC_InQueryCallContext::YIELD() {
  return getToken(CypherParser::YIELD, 0);
}

CypherParser::OC_YieldItemsContext* CypherParser::OC_InQueryCallContext::oC_YieldItems() {
  return getRuleContext<CypherParser::OC_YieldItemsContext>(0);
}


size_t CypherParser::OC_InQueryCallContext::getRuleIndex() const {
  return CypherParser::RuleOC_InQueryCall;
}

void CypherParser::OC_InQueryCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_InQueryCall(this);
}

void CypherParser::OC_InQueryCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_InQueryCall(this);
}


antlrcpp::Any CypherParser::OC_InQueryCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_InQueryCall(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_InQueryCallContext* CypherParser::oC_InQueryCall() {
  OC_InQueryCallContext *_localctx = _tracker.createInstance<OC_InQueryCallContext>(_ctx, getState());
  enterRule(_localctx, 40, CypherParser::RuleOC_InQueryCall);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(489);
    match(CypherParser::CALL);
    setState(490);
    match(CypherParser::SP);
    setState(491);
    oC_ExplicitProcedureInvocation();
    setState(498);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 59, _ctx)) {
    case 1: {
      setState(493);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(492);
        match(CypherParser::SP);
      }
      setState(495);
      match(CypherParser::YIELD);
      setState(496);
      match(CypherParser::SP);
      setState(497);
      oC_YieldItems();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_StandaloneCallContext ------------------------------------------------------------------

CypherParser::OC_StandaloneCallContext::OC_StandaloneCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_StandaloneCallContext::CALL() {
  return getToken(CypherParser::CALL, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_StandaloneCallContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_StandaloneCallContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_ExplicitProcedureInvocationContext* CypherParser::OC_StandaloneCallContext::oC_ExplicitProcedureInvocation() {
  return getRuleContext<CypherParser::OC_ExplicitProcedureInvocationContext>(0);
}

CypherParser::OC_ImplicitProcedureInvocationContext* CypherParser::OC_StandaloneCallContext::oC_ImplicitProcedureInvocation() {
  return getRuleContext<CypherParser::OC_ImplicitProcedureInvocationContext>(0);
}

tree::TerminalNode* CypherParser::OC_StandaloneCallContext::YIELD() {
  return getToken(CypherParser::YIELD, 0);
}

CypherParser::OC_YieldItemsContext* CypherParser::OC_StandaloneCallContext::oC_YieldItems() {
  return getRuleContext<CypherParser::OC_YieldItemsContext>(0);
}


size_t CypherParser::OC_StandaloneCallContext::getRuleIndex() const {
  return CypherParser::RuleOC_StandaloneCall;
}

void CypherParser::OC_StandaloneCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_StandaloneCall(this);
}

void CypherParser::OC_StandaloneCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_StandaloneCall(this);
}


antlrcpp::Any CypherParser::OC_StandaloneCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_StandaloneCall(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_StandaloneCallContext* CypherParser::oC_StandaloneCall() {
  OC_StandaloneCallContext *_localctx = _tracker.createInstance<OC_StandaloneCallContext>(_ctx, getState());
  enterRule(_localctx, 42, CypherParser::RuleOC_StandaloneCall);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(500);
    match(CypherParser::CALL);
    setState(501);
    match(CypherParser::SP);
    setState(504);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 60, _ctx)) {
    case 1: {
      setState(502);
      oC_ExplicitProcedureInvocation();
      break;
    }

    case 2: {
      setState(503);
      oC_ImplicitProcedureInvocation();
      break;
    }

    }
    setState(515);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 63, _ctx)) {
    case 1: {
      setState(507);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(506);
        match(CypherParser::SP);
      }
      setState(509);
      match(CypherParser::YIELD);
      setState(510);
      match(CypherParser::SP);
      setState(513);
      _errHandler->sync(this);
      switch (_input->LA(1)) {
        case CypherParser::T__4: {
          setState(511);
          match(CypherParser::T__4);
          break;
        }

        case CypherParser::COUNT:
        case CypherParser::ANY:
        case CypherParser::NONE:
        case CypherParser::SINGLE:
        case CypherParser::HexLetter:
        case CypherParser::FILTER:
        case CypherParser::EXTRACT:
        case CypherParser::UnescapedSymbolicName:
        case CypherParser::EscapedSymbolicName: {
          setState(512);
          oC_YieldItems();
          break;
        }

      default:
        throw NoViableAltException(this);
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_YieldItemsContext ------------------------------------------------------------------

CypherParser::OC_YieldItemsContext::OC_YieldItemsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_YieldItemContext *> CypherParser::OC_YieldItemsContext::oC_YieldItem() {
  return getRuleContexts<CypherParser::OC_YieldItemContext>();
}

CypherParser::OC_YieldItemContext* CypherParser::OC_YieldItemsContext::oC_YieldItem(size_t i) {
  return getRuleContext<CypherParser::OC_YieldItemContext>(i);
}

CypherParser::OC_WhereContext* CypherParser::OC_YieldItemsContext::oC_Where() {
  return getRuleContext<CypherParser::OC_WhereContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_YieldItemsContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_YieldItemsContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_YieldItemsContext::getRuleIndex() const {
  return CypherParser::RuleOC_YieldItems;
}

void CypherParser::OC_YieldItemsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_YieldItems(this);
}

void CypherParser::OC_YieldItemsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_YieldItems(this);
}


antlrcpp::Any CypherParser::OC_YieldItemsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_YieldItems(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_YieldItemsContext* CypherParser::oC_YieldItems() {
  OC_YieldItemsContext *_localctx = _tracker.createInstance<OC_YieldItemsContext>(_ctx, getState());
  enterRule(_localctx, 44, CypherParser::RuleOC_YieldItems);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(517);
    oC_YieldItem();
    setState(528);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(519);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(518);
          match(CypherParser::SP);
        }
        setState(521);
        match(CypherParser::T__1);
        setState(523);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(522);
          match(CypherParser::SP);
        }
        setState(525);
        oC_YieldItem(); 
      }
      setState(530);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 66, _ctx);
    }
    setState(535);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 68, _ctx)) {
    case 1: {
      setState(532);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(531);
        match(CypherParser::SP);
      }
      setState(534);
      oC_Where();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_YieldItemContext ------------------------------------------------------------------

CypherParser::OC_YieldItemContext::OC_YieldItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_VariableContext* CypherParser::OC_YieldItemContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_ProcedureResultFieldContext* CypherParser::OC_YieldItemContext::oC_ProcedureResultField() {
  return getRuleContext<CypherParser::OC_ProcedureResultFieldContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_YieldItemContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_YieldItemContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_YieldItemContext::AS() {
  return getToken(CypherParser::AS, 0);
}


size_t CypherParser::OC_YieldItemContext::getRuleIndex() const {
  return CypherParser::RuleOC_YieldItem;
}

void CypherParser::OC_YieldItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_YieldItem(this);
}

void CypherParser::OC_YieldItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_YieldItem(this);
}


antlrcpp::Any CypherParser::OC_YieldItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_YieldItem(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_YieldItemContext* CypherParser::oC_YieldItem() {
  OC_YieldItemContext *_localctx = _tracker.createInstance<OC_YieldItemContext>(_ctx, getState());
  enterRule(_localctx, 46, CypherParser::RuleOC_YieldItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(542);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 69, _ctx)) {
    case 1: {
      setState(537);
      oC_ProcedureResultField();
      setState(538);
      match(CypherParser::SP);
      setState(539);
      match(CypherParser::AS);
      setState(540);
      match(CypherParser::SP);
      break;
    }

    }
    setState(544);
    oC_Variable();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_WithContext ------------------------------------------------------------------

CypherParser::OC_WithContext::OC_WithContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_WithContext::WITH() {
  return getToken(CypherParser::WITH, 0);
}

CypherParser::OC_ProjectionBodyContext* CypherParser::OC_WithContext::oC_ProjectionBody() {
  return getRuleContext<CypherParser::OC_ProjectionBodyContext>(0);
}

CypherParser::OC_WhereContext* CypherParser::OC_WithContext::oC_Where() {
  return getRuleContext<CypherParser::OC_WhereContext>(0);
}

tree::TerminalNode* CypherParser::OC_WithContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_WithContext::getRuleIndex() const {
  return CypherParser::RuleOC_With;
}

void CypherParser::OC_WithContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_With(this);
}

void CypherParser::OC_WithContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_With(this);
}


antlrcpp::Any CypherParser::OC_WithContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_With(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_WithContext* CypherParser::oC_With() {
  OC_WithContext *_localctx = _tracker.createInstance<OC_WithContext>(_ctx, getState());
  enterRule(_localctx, 48, CypherParser::RuleOC_With);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(546);
    match(CypherParser::WITH);
    setState(547);
    oC_ProjectionBody();
    setState(552);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 71, _ctx)) {
    case 1: {
      setState(549);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(548);
        match(CypherParser::SP);
      }
      setState(551);
      oC_Where();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ReturnContext ------------------------------------------------------------------

CypherParser::OC_ReturnContext::OC_ReturnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_ReturnContext::RETURN() {
  return getToken(CypherParser::RETURN, 0);
}

CypherParser::OC_ProjectionBodyContext* CypherParser::OC_ReturnContext::oC_ProjectionBody() {
  return getRuleContext<CypherParser::OC_ProjectionBodyContext>(0);
}


size_t CypherParser::OC_ReturnContext::getRuleIndex() const {
  return CypherParser::RuleOC_Return;
}

void CypherParser::OC_ReturnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Return(this);
}

void CypherParser::OC_ReturnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Return(this);
}


antlrcpp::Any CypherParser::OC_ReturnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Return(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ReturnContext* CypherParser::oC_Return() {
  OC_ReturnContext *_localctx = _tracker.createInstance<OC_ReturnContext>(_ctx, getState());
  enterRule(_localctx, 50, CypherParser::RuleOC_Return);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(554);
    match(CypherParser::RETURN);
    setState(555);
    oC_ProjectionBody();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ProjectionBodyContext ------------------------------------------------------------------

CypherParser::OC_ProjectionBodyContext::OC_ProjectionBodyContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_ProjectionBodyContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ProjectionBodyContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_ProjectionItemsContext* CypherParser::OC_ProjectionBodyContext::oC_ProjectionItems() {
  return getRuleContext<CypherParser::OC_ProjectionItemsContext>(0);
}

tree::TerminalNode* CypherParser::OC_ProjectionBodyContext::DISTINCT() {
  return getToken(CypherParser::DISTINCT, 0);
}

CypherParser::OC_OrderContext* CypherParser::OC_ProjectionBodyContext::oC_Order() {
  return getRuleContext<CypherParser::OC_OrderContext>(0);
}

CypherParser::OC_SkipContext* CypherParser::OC_ProjectionBodyContext::oC_Skip() {
  return getRuleContext<CypherParser::OC_SkipContext>(0);
}

CypherParser::OC_LimitContext* CypherParser::OC_ProjectionBodyContext::oC_Limit() {
  return getRuleContext<CypherParser::OC_LimitContext>(0);
}


size_t CypherParser::OC_ProjectionBodyContext::getRuleIndex() const {
  return CypherParser::RuleOC_ProjectionBody;
}

void CypherParser::OC_ProjectionBodyContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ProjectionBody(this);
}

void CypherParser::OC_ProjectionBodyContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ProjectionBody(this);
}


antlrcpp::Any CypherParser::OC_ProjectionBodyContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ProjectionBody(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ProjectionBodyContext* CypherParser::oC_ProjectionBody() {
  OC_ProjectionBodyContext *_localctx = _tracker.createInstance<OC_ProjectionBodyContext>(_ctx, getState());
  enterRule(_localctx, 52, CypherParser::RuleOC_ProjectionBody);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(561);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 73, _ctx)) {
    case 1: {
      setState(558);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(557);
        match(CypherParser::SP);
      }
      setState(560);
      match(CypherParser::DISTINCT);
      break;
    }

    }
    setState(563);
    match(CypherParser::SP);
    setState(564);
    oC_ProjectionItems();
    setState(567);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 74, _ctx)) {
    case 1: {
      setState(565);
      match(CypherParser::SP);
      setState(566);
      oC_Order();
      break;
    }

    }
    setState(571);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 75, _ctx)) {
    case 1: {
      setState(569);
      match(CypherParser::SP);
      setState(570);
      oC_Skip();
      break;
    }

    }
    setState(575);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 76, _ctx)) {
    case 1: {
      setState(573);
      match(CypherParser::SP);
      setState(574);
      oC_Limit();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ProjectionItemsContext ------------------------------------------------------------------

CypherParser::OC_ProjectionItemsContext::OC_ProjectionItemsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_ProjectionItemContext *> CypherParser::OC_ProjectionItemsContext::oC_ProjectionItem() {
  return getRuleContexts<CypherParser::OC_ProjectionItemContext>();
}

CypherParser::OC_ProjectionItemContext* CypherParser::OC_ProjectionItemsContext::oC_ProjectionItem(size_t i) {
  return getRuleContext<CypherParser::OC_ProjectionItemContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ProjectionItemsContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ProjectionItemsContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_ProjectionItemsContext::getRuleIndex() const {
  return CypherParser::RuleOC_ProjectionItems;
}

void CypherParser::OC_ProjectionItemsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ProjectionItems(this);
}

void CypherParser::OC_ProjectionItemsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ProjectionItems(this);
}


antlrcpp::Any CypherParser::OC_ProjectionItemsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ProjectionItems(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ProjectionItemsContext* CypherParser::oC_ProjectionItems() {
  OC_ProjectionItemsContext *_localctx = _tracker.createInstance<OC_ProjectionItemsContext>(_ctx, getState());
  enterRule(_localctx, 54, CypherParser::RuleOC_ProjectionItems);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(605);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::T__4: {
        enterOuterAlt(_localctx, 1);
        setState(577);
        match(CypherParser::T__4);
        setState(588);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(579);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == CypherParser::SP) {
              setState(578);
              match(CypherParser::SP);
            }
            setState(581);
            match(CypherParser::T__1);
            setState(583);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == CypherParser::SP) {
              setState(582);
              match(CypherParser::SP);
            }
            setState(585);
            oC_ProjectionItem(); 
          }
          setState(590);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 79, _ctx);
        }
        break;
      }

      case CypherParser::T__5:
      case CypherParser::T__7:
      case CypherParser::T__17:
      case CypherParser::T__18:
      case CypherParser::T__23:
      case CypherParser::T__25:
      case CypherParser::UNION:
      case CypherParser::ALL:
      case CypherParser::OPTIONAL:
      case CypherParser::MATCH:
      case CypherParser::UNWIND:
      case CypherParser::AS:
      case CypherParser::MERGE:
      case CypherParser::ON:
      case CypherParser::CREATE:
      case CypherParser::SET:
      case CypherParser::DETACH:
      case CypherParser::DELETE:
      case CypherParser::REMOVE:
      case CypherParser::WITH:
      case CypherParser::RETURN:
      case CypherParser::DISTINCT:
      case CypherParser::ORDER:
      case CypherParser::BY:
      case CypherParser::L_SKIP:
      case CypherParser::LIMIT:
      case CypherParser::ASCENDING:
      case CypherParser::ASC:
      case CypherParser::DESCENDING:
      case CypherParser::DESC:
      case CypherParser::WHERE:
      case CypherParser::OR:
      case CypherParser::XOR:
      case CypherParser::AND:
      case CypherParser::NOT:
      case CypherParser::STARTS:
      case CypherParser::ENDS:
      case CypherParser::CONTAINS:
      case CypherParser::IN:
      case CypherParser::IS:
      case CypherParser::CypherNULL:
      case CypherParser::COUNT:
      case CypherParser::CASE:
      case CypherParser::ELSE:
      case CypherParser::END:
      case CypherParser::WHEN:
      case CypherParser::THEN:
      case CypherParser::ANY:
      case CypherParser::NONE:
      case CypherParser::SINGLE:
      case CypherParser::EXISTS:
      case CypherParser::TRUE:
      case CypherParser::FALSE:
      case CypherParser::HexInteger:
      case CypherParser::DecimalInteger:
      case CypherParser::OctalInteger:
      case CypherParser::HexLetter:
      case CypherParser::ExponentDecimalReal:
      case CypherParser::RegularDecimalReal:
      case CypherParser::StringLiteral:
      case CypherParser::CONSTRAINT:
      case CypherParser::DO:
      case CypherParser::FOR:
      case CypherParser::REQUIRE:
      case CypherParser::UNIQUE:
      case CypherParser::MANDATORY:
      case CypherParser::SCALAR:
      case CypherParser::OF:
      case CypherParser::ADD:
      case CypherParser::DROP:
      case CypherParser::FILTER:
      case CypherParser::EXTRACT:
      case CypherParser::UnescapedSymbolicName:
      case CypherParser::EscapedSymbolicName: {
        enterOuterAlt(_localctx, 2);
        setState(591);
        oC_ProjectionItem();
        setState(602);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
          if (alt == 1) {
            setState(593);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == CypherParser::SP) {
              setState(592);
              match(CypherParser::SP);
            }
            setState(595);
            match(CypherParser::T__1);
            setState(597);
            _errHandler->sync(this);

            _la = _input->LA(1);
            if (_la == CypherParser::SP) {
              setState(596);
              match(CypherParser::SP);
            }
            setState(599);
            oC_ProjectionItem(); 
          }
          setState(604);
          _errHandler->sync(this);
          alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 82, _ctx);
        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ProjectionItemContext ------------------------------------------------------------------

CypherParser::OC_ProjectionItemContext::OC_ProjectionItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ExpressionContext* CypherParser::OC_ProjectionItemContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ProjectionItemContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ProjectionItemContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_ProjectionItemContext::AS() {
  return getToken(CypherParser::AS, 0);
}

CypherParser::OC_VariableContext* CypherParser::OC_ProjectionItemContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}


size_t CypherParser::OC_ProjectionItemContext::getRuleIndex() const {
  return CypherParser::RuleOC_ProjectionItem;
}

void CypherParser::OC_ProjectionItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ProjectionItem(this);
}

void CypherParser::OC_ProjectionItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ProjectionItem(this);
}


antlrcpp::Any CypherParser::OC_ProjectionItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ProjectionItem(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ProjectionItemContext* CypherParser::oC_ProjectionItem() {
  OC_ProjectionItemContext *_localctx = _tracker.createInstance<OC_ProjectionItemContext>(_ctx, getState());
  enterRule(_localctx, 56, CypherParser::RuleOC_ProjectionItem);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(614);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 84, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(607);
      oC_Expression();
      setState(608);
      match(CypherParser::SP);
      setState(609);
      match(CypherParser::AS);
      setState(610);
      match(CypherParser::SP);
      setState(611);
      oC_Variable();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(613);
      oC_Expression();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_OrderContext ------------------------------------------------------------------

CypherParser::OC_OrderContext::OC_OrderContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_OrderContext::ORDER() {
  return getToken(CypherParser::ORDER, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_OrderContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_OrderContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_OrderContext::BY() {
  return getToken(CypherParser::BY, 0);
}

std::vector<CypherParser::OC_SortItemContext *> CypherParser::OC_OrderContext::oC_SortItem() {
  return getRuleContexts<CypherParser::OC_SortItemContext>();
}

CypherParser::OC_SortItemContext* CypherParser::OC_OrderContext::oC_SortItem(size_t i) {
  return getRuleContext<CypherParser::OC_SortItemContext>(i);
}


size_t CypherParser::OC_OrderContext::getRuleIndex() const {
  return CypherParser::RuleOC_Order;
}

void CypherParser::OC_OrderContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Order(this);
}

void CypherParser::OC_OrderContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Order(this);
}


antlrcpp::Any CypherParser::OC_OrderContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Order(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_OrderContext* CypherParser::oC_Order() {
  OC_OrderContext *_localctx = _tracker.createInstance<OC_OrderContext>(_ctx, getState());
  enterRule(_localctx, 58, CypherParser::RuleOC_Order);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(616);
    match(CypherParser::ORDER);
    setState(617);
    match(CypherParser::SP);
    setState(618);
    match(CypherParser::BY);
    setState(619);
    match(CypherParser::SP);
    setState(620);
    oC_SortItem();
    setState(628);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CypherParser::T__1) {
      setState(621);
      match(CypherParser::T__1);
      setState(623);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(622);
        match(CypherParser::SP);
      }
      setState(625);
      oC_SortItem();
      setState(630);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SkipContext ------------------------------------------------------------------

CypherParser::OC_SkipContext::OC_SkipContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_SkipContext::L_SKIP() {
  return getToken(CypherParser::L_SKIP, 0);
}

tree::TerminalNode* CypherParser::OC_SkipContext::SP() {
  return getToken(CypherParser::SP, 0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_SkipContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}


size_t CypherParser::OC_SkipContext::getRuleIndex() const {
  return CypherParser::RuleOC_Skip;
}

void CypherParser::OC_SkipContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Skip(this);
}

void CypherParser::OC_SkipContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Skip(this);
}


antlrcpp::Any CypherParser::OC_SkipContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Skip(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SkipContext* CypherParser::oC_Skip() {
  OC_SkipContext *_localctx = _tracker.createInstance<OC_SkipContext>(_ctx, getState());
  enterRule(_localctx, 60, CypherParser::RuleOC_Skip);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(631);
    match(CypherParser::L_SKIP);
    setState(632);
    match(CypherParser::SP);
    setState(633);
    oC_Expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_LimitContext ------------------------------------------------------------------

CypherParser::OC_LimitContext::OC_LimitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_LimitContext::LIMIT() {
  return getToken(CypherParser::LIMIT, 0);
}

tree::TerminalNode* CypherParser::OC_LimitContext::SP() {
  return getToken(CypherParser::SP, 0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_LimitContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}


size_t CypherParser::OC_LimitContext::getRuleIndex() const {
  return CypherParser::RuleOC_Limit;
}

void CypherParser::OC_LimitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Limit(this);
}

void CypherParser::OC_LimitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Limit(this);
}


antlrcpp::Any CypherParser::OC_LimitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Limit(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_LimitContext* CypherParser::oC_Limit() {
  OC_LimitContext *_localctx = _tracker.createInstance<OC_LimitContext>(_ctx, getState());
  enterRule(_localctx, 62, CypherParser::RuleOC_Limit);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(635);
    match(CypherParser::LIMIT);
    setState(636);
    match(CypherParser::SP);
    setState(637);
    oC_Expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SortItemContext ------------------------------------------------------------------

CypherParser::OC_SortItemContext::OC_SortItemContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ExpressionContext* CypherParser::OC_SortItemContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}

tree::TerminalNode* CypherParser::OC_SortItemContext::ASCENDING() {
  return getToken(CypherParser::ASCENDING, 0);
}

tree::TerminalNode* CypherParser::OC_SortItemContext::ASC() {
  return getToken(CypherParser::ASC, 0);
}

tree::TerminalNode* CypherParser::OC_SortItemContext::DESCENDING() {
  return getToken(CypherParser::DESCENDING, 0);
}

tree::TerminalNode* CypherParser::OC_SortItemContext::DESC() {
  return getToken(CypherParser::DESC, 0);
}

tree::TerminalNode* CypherParser::OC_SortItemContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_SortItemContext::getRuleIndex() const {
  return CypherParser::RuleOC_SortItem;
}

void CypherParser::OC_SortItemContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_SortItem(this);
}

void CypherParser::OC_SortItemContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_SortItem(this);
}


antlrcpp::Any CypherParser::OC_SortItemContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_SortItem(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SortItemContext* CypherParser::oC_SortItem() {
  OC_SortItemContext *_localctx = _tracker.createInstance<OC_SortItemContext>(_ctx, getState());
  enterRule(_localctx, 64, CypherParser::RuleOC_SortItem);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(639);
    oC_Expression();
    setState(644);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 88, _ctx)) {
    case 1: {
      setState(641);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(640);
        match(CypherParser::SP);
      }
      setState(643);
      _la = _input->LA(1);
      if (!(((((_la - 68) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 68)) & ((1ULL << (CypherParser::ASCENDING - 68))
        | (1ULL << (CypherParser::ASC - 68))
        | (1ULL << (CypherParser::DESCENDING - 68))
        | (1ULL << (CypherParser::DESC - 68)))) != 0))) {
      _errHandler->recoverInline(this);
      }
      else {
        _errHandler->reportMatch(this);
        consume();
      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_WhereContext ------------------------------------------------------------------

CypherParser::OC_WhereContext::OC_WhereContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_WhereContext::WHERE() {
  return getToken(CypherParser::WHERE, 0);
}

tree::TerminalNode* CypherParser::OC_WhereContext::SP() {
  return getToken(CypherParser::SP, 0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_WhereContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}


size_t CypherParser::OC_WhereContext::getRuleIndex() const {
  return CypherParser::RuleOC_Where;
}

void CypherParser::OC_WhereContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Where(this);
}

void CypherParser::OC_WhereContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Where(this);
}


antlrcpp::Any CypherParser::OC_WhereContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Where(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_WhereContext* CypherParser::oC_Where() {
  OC_WhereContext *_localctx = _tracker.createInstance<OC_WhereContext>(_ctx, getState());
  enterRule(_localctx, 66, CypherParser::RuleOC_Where);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(646);
    match(CypherParser::WHERE);
    setState(647);
    match(CypherParser::SP);
    setState(648);
    oC_Expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PatternContext ------------------------------------------------------------------

CypherParser::OC_PatternContext::OC_PatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_PatternPartContext *> CypherParser::OC_PatternContext::oC_PatternPart() {
  return getRuleContexts<CypherParser::OC_PatternPartContext>();
}

CypherParser::OC_PatternPartContext* CypherParser::OC_PatternContext::oC_PatternPart(size_t i) {
  return getRuleContext<CypherParser::OC_PatternPartContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PatternContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PatternContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_PatternContext::getRuleIndex() const {
  return CypherParser::RuleOC_Pattern;
}

void CypherParser::OC_PatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Pattern(this);
}

void CypherParser::OC_PatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Pattern(this);
}


antlrcpp::Any CypherParser::OC_PatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Pattern(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PatternContext* CypherParser::oC_Pattern() {
  OC_PatternContext *_localctx = _tracker.createInstance<OC_PatternContext>(_ctx, getState());
  enterRule(_localctx, 68, CypherParser::RuleOC_Pattern);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(650);
    oC_PatternPart();
    setState(661);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(652);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(651);
          match(CypherParser::SP);
        }
        setState(654);
        match(CypherParser::T__1);
        setState(656);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(655);
          match(CypherParser::SP);
        }
        setState(658);
        oC_PatternPart(); 
      }
      setState(663);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 91, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PatternPartContext ------------------------------------------------------------------

CypherParser::OC_PatternPartContext::OC_PatternPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_VariableContext* CypherParser::OC_PatternPartContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_AnonymousPatternPartContext* CypherParser::OC_PatternPartContext::oC_AnonymousPatternPart() {
  return getRuleContext<CypherParser::OC_AnonymousPatternPartContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PatternPartContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PatternPartContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_PatternPartContext::getRuleIndex() const {
  return CypherParser::RuleOC_PatternPart;
}

void CypherParser::OC_PatternPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PatternPart(this);
}

void CypherParser::OC_PatternPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PatternPart(this);
}


antlrcpp::Any CypherParser::OC_PatternPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PatternPart(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PatternPartContext* CypherParser::oC_PatternPart() {
  OC_PatternPartContext *_localctx = _tracker.createInstance<OC_PatternPartContext>(_ctx, getState());
  enterRule(_localctx, 70, CypherParser::RuleOC_PatternPart);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(675);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 94, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(664);
      oC_Variable();
      setState(666);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(665);
        match(CypherParser::SP);
      }
      setState(668);
      match(CypherParser::T__2);
      setState(670);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(669);
        match(CypherParser::SP);
      }
      setState(672);
      oC_AnonymousPatternPart();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(674);
      oC_AnonymousPatternPart();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_AnonymousPatternPartContext ------------------------------------------------------------------

CypherParser::OC_AnonymousPatternPartContext::OC_AnonymousPatternPartContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ShortestPathPatternContext* CypherParser::OC_AnonymousPatternPartContext::oC_ShortestPathPattern() {
  return getRuleContext<CypherParser::OC_ShortestPathPatternContext>(0);
}

CypherParser::OC_PatternElementContext* CypherParser::OC_AnonymousPatternPartContext::oC_PatternElement() {
  return getRuleContext<CypherParser::OC_PatternElementContext>(0);
}


size_t CypherParser::OC_AnonymousPatternPartContext::getRuleIndex() const {
  return CypherParser::RuleOC_AnonymousPatternPart;
}

void CypherParser::OC_AnonymousPatternPartContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_AnonymousPatternPart(this);
}

void CypherParser::OC_AnonymousPatternPartContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_AnonymousPatternPart(this);
}


antlrcpp::Any CypherParser::OC_AnonymousPatternPartContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_AnonymousPatternPart(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_AnonymousPatternPartContext* CypherParser::oC_AnonymousPatternPart() {
  OC_AnonymousPatternPartContext *_localctx = _tracker.createInstance<OC_AnonymousPatternPartContext>(_ctx, getState());
  enterRule(_localctx, 72, CypherParser::RuleOC_AnonymousPatternPart);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(679);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::COUNT:
      case CypherParser::ANY:
      case CypherParser::NONE:
      case CypherParser::SINGLE:
      case CypherParser::HexLetter:
      case CypherParser::FILTER:
      case CypherParser::EXTRACT:
      case CypherParser::UnescapedSymbolicName:
      case CypherParser::EscapedSymbolicName: {
        enterOuterAlt(_localctx, 1);
        setState(677);
        oC_ShortestPathPattern();
        break;
      }

      case CypherParser::T__5: {
        enterOuterAlt(_localctx, 2);
        setState(678);
        oC_PatternElement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ShortestPathPatternContext ------------------------------------------------------------------

CypherParser::OC_ShortestPathPatternContext::OC_ShortestPathPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SymbolicNameContext* CypherParser::OC_ShortestPathPatternContext::oC_SymbolicName() {
  return getRuleContext<CypherParser::OC_SymbolicNameContext>(0);
}

CypherParser::OC_PatternElementContext* CypherParser::OC_ShortestPathPatternContext::oC_PatternElement() {
  return getRuleContext<CypherParser::OC_PatternElementContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ShortestPathPatternContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ShortestPathPatternContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_ShortestPathPatternContext::getRuleIndex() const {
  return CypherParser::RuleOC_ShortestPathPattern;
}

void CypherParser::OC_ShortestPathPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ShortestPathPattern(this);
}

void CypherParser::OC_ShortestPathPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ShortestPathPattern(this);
}


antlrcpp::Any CypherParser::OC_ShortestPathPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ShortestPathPattern(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ShortestPathPatternContext* CypherParser::oC_ShortestPathPattern() {
  OC_ShortestPathPatternContext *_localctx = _tracker.createInstance<OC_ShortestPathPatternContext>(_ctx, getState());
  enterRule(_localctx, 74, CypherParser::RuleOC_ShortestPathPattern);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(681);
    oC_SymbolicName();
    setState(683);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(682);
      match(CypherParser::SP);
    }
    setState(685);
    match(CypherParser::T__5);
    setState(687);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(686);
      match(CypherParser::SP);
    }
    setState(689);
    oC_PatternElement();
    setState(690);
    match(CypherParser::T__6);
    setState(692);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 98, _ctx)) {
    case 1: {
      setState(691);
      match(CypherParser::SP);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PatternElementContext ------------------------------------------------------------------

CypherParser::OC_PatternElementContext::OC_PatternElementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_NodePatternContext* CypherParser::OC_PatternElementContext::oC_NodePattern() {
  return getRuleContext<CypherParser::OC_NodePatternContext>(0);
}

std::vector<CypherParser::OC_PatternElementChainContext *> CypherParser::OC_PatternElementContext::oC_PatternElementChain() {
  return getRuleContexts<CypherParser::OC_PatternElementChainContext>();
}

CypherParser::OC_PatternElementChainContext* CypherParser::OC_PatternElementContext::oC_PatternElementChain(size_t i) {
  return getRuleContext<CypherParser::OC_PatternElementChainContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PatternElementContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PatternElementContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_PatternElementContext* CypherParser::OC_PatternElementContext::oC_PatternElement() {
  return getRuleContext<CypherParser::OC_PatternElementContext>(0);
}


size_t CypherParser::OC_PatternElementContext::getRuleIndex() const {
  return CypherParser::RuleOC_PatternElement;
}

void CypherParser::OC_PatternElementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PatternElement(this);
}

void CypherParser::OC_PatternElementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PatternElement(this);
}


antlrcpp::Any CypherParser::OC_PatternElementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PatternElement(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PatternElementContext* CypherParser::oC_PatternElement() {
  OC_PatternElementContext *_localctx = _tracker.createInstance<OC_PatternElementContext>(_ctx, getState());
  enterRule(_localctx, 76, CypherParser::RuleOC_PatternElement);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    setState(713);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 103, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(694);
      oC_NodePattern();
      setState(701);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx);
      while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
        if (alt == 1) {
          setState(696);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(695);
            match(CypherParser::SP);
          }
          setState(698);
          oC_PatternElementChain(); 
        }
        setState(703);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 100, _ctx);
      }
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(704);
      match(CypherParser::T__5);
      setState(706);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(705);
        match(CypherParser::SP);
      }
      setState(708);
      oC_PatternElement();
      setState(709);
      match(CypherParser::T__6);
      setState(711);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 102, _ctx)) {
      case 1: {
        setState(710);
        match(CypherParser::SP);
        break;
      }

      }
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RelationshipsPatternContext ------------------------------------------------------------------

CypherParser::OC_RelationshipsPatternContext::OC_RelationshipsPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_NodePatternContext* CypherParser::OC_RelationshipsPatternContext::oC_NodePattern() {
  return getRuleContext<CypherParser::OC_NodePatternContext>(0);
}

std::vector<CypherParser::OC_PatternElementChainContext *> CypherParser::OC_RelationshipsPatternContext::oC_PatternElementChain() {
  return getRuleContexts<CypherParser::OC_PatternElementChainContext>();
}

CypherParser::OC_PatternElementChainContext* CypherParser::OC_RelationshipsPatternContext::oC_PatternElementChain(size_t i) {
  return getRuleContext<CypherParser::OC_PatternElementChainContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_RelationshipsPatternContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RelationshipsPatternContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_RelationshipsPatternContext::getRuleIndex() const {
  return CypherParser::RuleOC_RelationshipsPattern;
}

void CypherParser::OC_RelationshipsPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RelationshipsPattern(this);
}

void CypherParser::OC_RelationshipsPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RelationshipsPattern(this);
}


antlrcpp::Any CypherParser::OC_RelationshipsPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RelationshipsPattern(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RelationshipsPatternContext* CypherParser::oC_RelationshipsPattern() {
  OC_RelationshipsPatternContext *_localctx = _tracker.createInstance<OC_RelationshipsPatternContext>(_ctx, getState());
  enterRule(_localctx, 78, CypherParser::RuleOC_RelationshipsPattern);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(715);
    oC_NodePattern();
    setState(720); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(717);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == CypherParser::SP) {
                setState(716);
                match(CypherParser::SP);
              }
              setState(719);
              oC_PatternElementChain();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(722); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 105, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NodePatternContext ------------------------------------------------------------------

CypherParser::OC_NodePatternContext::OC_NodePatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_NodePatternContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_NodePatternContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_VariableContext* CypherParser::OC_NodePatternContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_NodeLabelsContext* CypherParser::OC_NodePatternContext::oC_NodeLabels() {
  return getRuleContext<CypherParser::OC_NodeLabelsContext>(0);
}

CypherParser::OC_PropertiesContext* CypherParser::OC_NodePatternContext::oC_Properties() {
  return getRuleContext<CypherParser::OC_PropertiesContext>(0);
}


size_t CypherParser::OC_NodePatternContext::getRuleIndex() const {
  return CypherParser::RuleOC_NodePattern;
}

void CypherParser::OC_NodePatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_NodePattern(this);
}

void CypherParser::OC_NodePatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_NodePattern(this);
}


antlrcpp::Any CypherParser::OC_NodePatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_NodePattern(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NodePatternContext* CypherParser::oC_NodePattern() {
  OC_NodePatternContext *_localctx = _tracker.createInstance<OC_NodePatternContext>(_ctx, getState());
  enterRule(_localctx, 80, CypherParser::RuleOC_NodePattern);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(724);
    match(CypherParser::T__5);
    setState(726);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(725);
      match(CypherParser::SP);
    }
    setState(732);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (CypherParser::COUNT - 83))
      | (1ULL << (CypherParser::ANY - 83))
      | (1ULL << (CypherParser::NONE - 83))
      | (1ULL << (CypherParser::SINGLE - 83))
      | (1ULL << (CypherParser::HexLetter - 83))
      | (1ULL << (CypherParser::FILTER - 83))
      | (1ULL << (CypherParser::EXTRACT - 83))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 83))
      | (1ULL << (CypherParser::EscapedSymbolicName - 83)))) != 0)) {
      setState(728);
      oC_Variable();
      setState(730);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(729);
        match(CypherParser::SP);
      }
    }
    setState(738);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::T__9) {
      setState(734);
      oC_NodeLabels();
      setState(736);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(735);
        match(CypherParser::SP);
      }
    }
    setState(744);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::T__23

    || _la == CypherParser::T__25) {
      setState(740);
      oC_Properties();
      setState(742);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(741);
        match(CypherParser::SP);
      }
    }
    setState(746);
    match(CypherParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PatternElementChainContext ------------------------------------------------------------------

CypherParser::OC_PatternElementChainContext::OC_PatternElementChainContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_RelationshipPatternContext* CypherParser::OC_PatternElementChainContext::oC_RelationshipPattern() {
  return getRuleContext<CypherParser::OC_RelationshipPatternContext>(0);
}

CypherParser::OC_NodePatternContext* CypherParser::OC_PatternElementChainContext::oC_NodePattern() {
  return getRuleContext<CypherParser::OC_NodePatternContext>(0);
}

tree::TerminalNode* CypherParser::OC_PatternElementChainContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_PatternElementChainContext::getRuleIndex() const {
  return CypherParser::RuleOC_PatternElementChain;
}

void CypherParser::OC_PatternElementChainContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PatternElementChain(this);
}

void CypherParser::OC_PatternElementChainContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PatternElementChain(this);
}


antlrcpp::Any CypherParser::OC_PatternElementChainContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PatternElementChain(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PatternElementChainContext* CypherParser::oC_PatternElementChain() {
  OC_PatternElementChainContext *_localctx = _tracker.createInstance<OC_PatternElementChainContext>(_ctx, getState());
  enterRule(_localctx, 82, CypherParser::RuleOC_PatternElementChain);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(748);
    oC_RelationshipPattern();
    setState(750);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(749);
      match(CypherParser::SP);
    }
    setState(752);
    oC_NodePattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RelationshipPatternContext ------------------------------------------------------------------

CypherParser::OC_RelationshipPatternContext::OC_RelationshipPatternContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_LeftArrowHeadContext* CypherParser::OC_RelationshipPatternContext::oC_LeftArrowHead() {
  return getRuleContext<CypherParser::OC_LeftArrowHeadContext>(0);
}

std::vector<CypherParser::OC_DashContext *> CypherParser::OC_RelationshipPatternContext::oC_Dash() {
  return getRuleContexts<CypherParser::OC_DashContext>();
}

CypherParser::OC_DashContext* CypherParser::OC_RelationshipPatternContext::oC_Dash(size_t i) {
  return getRuleContext<CypherParser::OC_DashContext>(i);
}

CypherParser::OC_RightArrowHeadContext* CypherParser::OC_RelationshipPatternContext::oC_RightArrowHead() {
  return getRuleContext<CypherParser::OC_RightArrowHeadContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_RelationshipPatternContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RelationshipPatternContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_RelationshipDetailContext* CypherParser::OC_RelationshipPatternContext::oC_RelationshipDetail() {
  return getRuleContext<CypherParser::OC_RelationshipDetailContext>(0);
}


size_t CypherParser::OC_RelationshipPatternContext::getRuleIndex() const {
  return CypherParser::RuleOC_RelationshipPattern;
}

void CypherParser::OC_RelationshipPatternContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RelationshipPattern(this);
}

void CypherParser::OC_RelationshipPatternContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RelationshipPattern(this);
}


antlrcpp::Any CypherParser::OC_RelationshipPatternContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RelationshipPattern(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RelationshipPatternContext* CypherParser::oC_RelationshipPattern() {
  OC_RelationshipPatternContext *_localctx = _tracker.createInstance<OC_RelationshipPatternContext>(_ctx, getState());
  enterRule(_localctx, 84, CypherParser::RuleOC_RelationshipPattern);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(818);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 130, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(754);
      oC_LeftArrowHead();
      setState(756);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(755);
        match(CypherParser::SP);
      }
      setState(758);
      oC_Dash();
      setState(760);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 115, _ctx)) {
      case 1: {
        setState(759);
        match(CypherParser::SP);
        break;
      }

      }
      setState(763);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::T__7) {
        setState(762);
        oC_RelationshipDetail();
      }
      setState(766);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(765);
        match(CypherParser::SP);
      }
      setState(768);
      oC_Dash();
      setState(770);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(769);
        match(CypherParser::SP);
      }
      setState(772);
      oC_RightArrowHead();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(774);
      oC_LeftArrowHead();
      setState(776);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(775);
        match(CypherParser::SP);
      }
      setState(778);
      oC_Dash();
      setState(780);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 120, _ctx)) {
      case 1: {
        setState(779);
        match(CypherParser::SP);
        break;
      }

      }
      setState(783);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::T__7) {
        setState(782);
        oC_RelationshipDetail();
      }
      setState(786);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(785);
        match(CypherParser::SP);
      }
      setState(788);
      oC_Dash();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(790);
      oC_Dash();
      setState(792);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 123, _ctx)) {
      case 1: {
        setState(791);
        match(CypherParser::SP);
        break;
      }

      }
      setState(795);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::T__7) {
        setState(794);
        oC_RelationshipDetail();
      }
      setState(798);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(797);
        match(CypherParser::SP);
      }
      setState(800);
      oC_Dash();
      setState(802);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(801);
        match(CypherParser::SP);
      }
      setState(804);
      oC_RightArrowHead();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(806);
      oC_Dash();
      setState(808);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 127, _ctx)) {
      case 1: {
        setState(807);
        match(CypherParser::SP);
        break;
      }

      }
      setState(811);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::T__7) {
        setState(810);
        oC_RelationshipDetail();
      }
      setState(814);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(813);
        match(CypherParser::SP);
      }
      setState(816);
      oC_Dash();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RelationshipDetailContext ------------------------------------------------------------------

CypherParser::OC_RelationshipDetailContext::OC_RelationshipDetailContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_RelationshipDetailContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RelationshipDetailContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_VariableContext* CypherParser::OC_RelationshipDetailContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_RelationshipTypesContext* CypherParser::OC_RelationshipDetailContext::oC_RelationshipTypes() {
  return getRuleContext<CypherParser::OC_RelationshipTypesContext>(0);
}

CypherParser::OC_RangeLiteralContext* CypherParser::OC_RelationshipDetailContext::oC_RangeLiteral() {
  return getRuleContext<CypherParser::OC_RangeLiteralContext>(0);
}

CypherParser::OC_PropertiesContext* CypherParser::OC_RelationshipDetailContext::oC_Properties() {
  return getRuleContext<CypherParser::OC_PropertiesContext>(0);
}


size_t CypherParser::OC_RelationshipDetailContext::getRuleIndex() const {
  return CypherParser::RuleOC_RelationshipDetail;
}

void CypherParser::OC_RelationshipDetailContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RelationshipDetail(this);
}

void CypherParser::OC_RelationshipDetailContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RelationshipDetail(this);
}


antlrcpp::Any CypherParser::OC_RelationshipDetailContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RelationshipDetail(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RelationshipDetailContext* CypherParser::oC_RelationshipDetail() {
  OC_RelationshipDetailContext *_localctx = _tracker.createInstance<OC_RelationshipDetailContext>(_ctx, getState());
  enterRule(_localctx, 86, CypherParser::RuleOC_RelationshipDetail);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(820);
    match(CypherParser::T__7);
    setState(822);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(821);
      match(CypherParser::SP);
    }
    setState(828);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (CypherParser::COUNT - 83))
      | (1ULL << (CypherParser::ANY - 83))
      | (1ULL << (CypherParser::NONE - 83))
      | (1ULL << (CypherParser::SINGLE - 83))
      | (1ULL << (CypherParser::HexLetter - 83))
      | (1ULL << (CypherParser::FILTER - 83))
      | (1ULL << (CypherParser::EXTRACT - 83))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 83))
      | (1ULL << (CypherParser::EscapedSymbolicName - 83)))) != 0)) {
      setState(824);
      oC_Variable();
      setState(826);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(825);
        match(CypherParser::SP);
      }
    }
    setState(834);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::T__9) {
      setState(830);
      oC_RelationshipTypes();
      setState(832);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(831);
        match(CypherParser::SP);
      }
    }
    setState(837);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::T__4) {
      setState(836);
      oC_RangeLiteral();
    }
    setState(843);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::T__23

    || _la == CypherParser::T__25) {
      setState(839);
      oC_Properties();
      setState(841);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(840);
        match(CypherParser::SP);
      }
    }
    setState(845);
    match(CypherParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PropertiesContext ------------------------------------------------------------------

CypherParser::OC_PropertiesContext::OC_PropertiesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_MapLiteralContext* CypherParser::OC_PropertiesContext::oC_MapLiteral() {
  return getRuleContext<CypherParser::OC_MapLiteralContext>(0);
}

CypherParser::OC_ParameterContext* CypherParser::OC_PropertiesContext::oC_Parameter() {
  return getRuleContext<CypherParser::OC_ParameterContext>(0);
}


size_t CypherParser::OC_PropertiesContext::getRuleIndex() const {
  return CypherParser::RuleOC_Properties;
}

void CypherParser::OC_PropertiesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Properties(this);
}

void CypherParser::OC_PropertiesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Properties(this);
}


antlrcpp::Any CypherParser::OC_PropertiesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Properties(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PropertiesContext* CypherParser::oC_Properties() {
  OC_PropertiesContext *_localctx = _tracker.createInstance<OC_PropertiesContext>(_ctx, getState());
  enterRule(_localctx, 88, CypherParser::RuleOC_Properties);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(849);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::T__23: {
        enterOuterAlt(_localctx, 1);
        setState(847);
        oC_MapLiteral();
        break;
      }

      case CypherParser::T__25: {
        enterOuterAlt(_localctx, 2);
        setState(848);
        oC_Parameter();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RelationshipTypesContext ------------------------------------------------------------------

CypherParser::OC_RelationshipTypesContext::OC_RelationshipTypesContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_RelTypeNameContext *> CypherParser::OC_RelationshipTypesContext::oC_RelTypeName() {
  return getRuleContexts<CypherParser::OC_RelTypeNameContext>();
}

CypherParser::OC_RelTypeNameContext* CypherParser::OC_RelationshipTypesContext::oC_RelTypeName(size_t i) {
  return getRuleContext<CypherParser::OC_RelTypeNameContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_RelationshipTypesContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RelationshipTypesContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_RelationshipTypesContext::getRuleIndex() const {
  return CypherParser::RuleOC_RelationshipTypes;
}

void CypherParser::OC_RelationshipTypesContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RelationshipTypes(this);
}

void CypherParser::OC_RelationshipTypesContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RelationshipTypes(this);
}


antlrcpp::Any CypherParser::OC_RelationshipTypesContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RelationshipTypes(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RelationshipTypesContext* CypherParser::oC_RelationshipTypes() {
  OC_RelationshipTypesContext *_localctx = _tracker.createInstance<OC_RelationshipTypesContext>(_ctx, getState());
  enterRule(_localctx, 90, CypherParser::RuleOC_RelationshipTypes);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(851);
    match(CypherParser::T__9);
    setState(853);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(852);
      match(CypherParser::SP);
    }
    setState(855);
    oC_RelTypeName();
    setState(869);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 144, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(857);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(856);
          match(CypherParser::SP);
        }
        setState(859);
        match(CypherParser::T__10);
        setState(861);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::T__9) {
          setState(860);
          match(CypherParser::T__9);
        }
        setState(864);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(863);
          match(CypherParser::SP);
        }
        setState(866);
        oC_RelTypeName(); 
      }
      setState(871);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 144, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NodeLabelsContext ------------------------------------------------------------------

CypherParser::OC_NodeLabelsContext::OC_NodeLabelsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_NodeLabelContext *> CypherParser::OC_NodeLabelsContext::oC_NodeLabel() {
  return getRuleContexts<CypherParser::OC_NodeLabelContext>();
}

CypherParser::OC_NodeLabelContext* CypherParser::OC_NodeLabelsContext::oC_NodeLabel(size_t i) {
  return getRuleContext<CypherParser::OC_NodeLabelContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_NodeLabelsContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_NodeLabelsContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_NodeLabelsContext::getRuleIndex() const {
  return CypherParser::RuleOC_NodeLabels;
}

void CypherParser::OC_NodeLabelsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_NodeLabels(this);
}

void CypherParser::OC_NodeLabelsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_NodeLabels(this);
}


antlrcpp::Any CypherParser::OC_NodeLabelsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_NodeLabels(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NodeLabelsContext* CypherParser::oC_NodeLabels() {
  OC_NodeLabelsContext *_localctx = _tracker.createInstance<OC_NodeLabelsContext>(_ctx, getState());
  enterRule(_localctx, 92, CypherParser::RuleOC_NodeLabels);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(872);
    oC_NodeLabel();
    setState(879);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 146, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(874);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(873);
          match(CypherParser::SP);
        }
        setState(876);
        oC_NodeLabel(); 
      }
      setState(881);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 146, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NodeLabelContext ------------------------------------------------------------------

CypherParser::OC_NodeLabelContext::OC_NodeLabelContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_LabelNameContext* CypherParser::OC_NodeLabelContext::oC_LabelName() {
  return getRuleContext<CypherParser::OC_LabelNameContext>(0);
}

tree::TerminalNode* CypherParser::OC_NodeLabelContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_NodeLabelContext::getRuleIndex() const {
  return CypherParser::RuleOC_NodeLabel;
}

void CypherParser::OC_NodeLabelContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_NodeLabel(this);
}

void CypherParser::OC_NodeLabelContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_NodeLabel(this);
}


antlrcpp::Any CypherParser::OC_NodeLabelContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_NodeLabel(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NodeLabelContext* CypherParser::oC_NodeLabel() {
  OC_NodeLabelContext *_localctx = _tracker.createInstance<OC_NodeLabelContext>(_ctx, getState());
  enterRule(_localctx, 94, CypherParser::RuleOC_NodeLabel);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(882);
    match(CypherParser::T__9);
    setState(884);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(883);
      match(CypherParser::SP);
    }
    setState(886);
    oC_LabelName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RangeLiteralContext ------------------------------------------------------------------

CypherParser::OC_RangeLiteralContext::OC_RangeLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_RangeLiteralContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_RangeLiteralContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_IntegerLiteralContext *> CypherParser::OC_RangeLiteralContext::oC_IntegerLiteral() {
  return getRuleContexts<CypherParser::OC_IntegerLiteralContext>();
}

CypherParser::OC_IntegerLiteralContext* CypherParser::OC_RangeLiteralContext::oC_IntegerLiteral(size_t i) {
  return getRuleContext<CypherParser::OC_IntegerLiteralContext>(i);
}


size_t CypherParser::OC_RangeLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_RangeLiteral;
}

void CypherParser::OC_RangeLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RangeLiteral(this);
}

void CypherParser::OC_RangeLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RangeLiteral(this);
}


antlrcpp::Any CypherParser::OC_RangeLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RangeLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RangeLiteralContext* CypherParser::oC_RangeLiteral() {
  OC_RangeLiteralContext *_localctx = _tracker.createInstance<OC_RangeLiteralContext>(_ctx, getState());
  enterRule(_localctx, 96, CypherParser::RuleOC_RangeLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(888);
    match(CypherParser::T__4);
    setState(890);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(889);
      match(CypherParser::SP);
    }
    setState(896);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 95) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 95)) & ((1ULL << (CypherParser::HexInteger - 95))
      | (1ULL << (CypherParser::DecimalInteger - 95))
      | (1ULL << (CypherParser::OctalInteger - 95)))) != 0)) {
      setState(892);
      oC_IntegerLiteral();
      setState(894);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(893);
        match(CypherParser::SP);
      }
    }
    setState(908);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::T__11) {
      setState(898);
      match(CypherParser::T__11);
      setState(900);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(899);
        match(CypherParser::SP);
      }
      setState(906);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (((((_la - 95) & ~ 0x3fULL) == 0) &&
        ((1ULL << (_la - 95)) & ((1ULL << (CypherParser::HexInteger - 95))
        | (1ULL << (CypherParser::DecimalInteger - 95))
        | (1ULL << (CypherParser::OctalInteger - 95)))) != 0)) {
        setState(902);
        oC_IntegerLiteral();
        setState(904);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(903);
          match(CypherParser::SP);
        }
      }
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_LabelNameContext ------------------------------------------------------------------

CypherParser::OC_LabelNameContext::OC_LabelNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SchemaNameContext* CypherParser::OC_LabelNameContext::oC_SchemaName() {
  return getRuleContext<CypherParser::OC_SchemaNameContext>(0);
}


size_t CypherParser::OC_LabelNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_LabelName;
}

void CypherParser::OC_LabelNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_LabelName(this);
}

void CypherParser::OC_LabelNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_LabelName(this);
}


antlrcpp::Any CypherParser::OC_LabelNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_LabelName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_LabelNameContext* CypherParser::oC_LabelName() {
  OC_LabelNameContext *_localctx = _tracker.createInstance<OC_LabelNameContext>(_ctx, getState());
  enterRule(_localctx, 98, CypherParser::RuleOC_LabelName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(910);
    oC_SchemaName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RelTypeNameContext ------------------------------------------------------------------

CypherParser::OC_RelTypeNameContext::OC_RelTypeNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SchemaNameContext* CypherParser::OC_RelTypeNameContext::oC_SchemaName() {
  return getRuleContext<CypherParser::OC_SchemaNameContext>(0);
}


size_t CypherParser::OC_RelTypeNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_RelTypeName;
}

void CypherParser::OC_RelTypeNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RelTypeName(this);
}

void CypherParser::OC_RelTypeNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RelTypeName(this);
}


antlrcpp::Any CypherParser::OC_RelTypeNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RelTypeName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RelTypeNameContext* CypherParser::oC_RelTypeName() {
  OC_RelTypeNameContext *_localctx = _tracker.createInstance<OC_RelTypeNameContext>(_ctx, getState());
  enterRule(_localctx, 100, CypherParser::RuleOC_RelTypeName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(912);
    oC_SchemaName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PropertyExpressionContext ------------------------------------------------------------------

CypherParser::OC_PropertyExpressionContext::OC_PropertyExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_AtomContext* CypherParser::OC_PropertyExpressionContext::oC_Atom() {
  return getRuleContext<CypherParser::OC_AtomContext>(0);
}

std::vector<CypherParser::OC_PropertyLookupContext *> CypherParser::OC_PropertyExpressionContext::oC_PropertyLookup() {
  return getRuleContexts<CypherParser::OC_PropertyLookupContext>();
}

CypherParser::OC_PropertyLookupContext* CypherParser::OC_PropertyExpressionContext::oC_PropertyLookup(size_t i) {
  return getRuleContext<CypherParser::OC_PropertyLookupContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PropertyExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PropertyExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_PropertyExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_PropertyExpression;
}

void CypherParser::OC_PropertyExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PropertyExpression(this);
}

void CypherParser::OC_PropertyExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PropertyExpression(this);
}


antlrcpp::Any CypherParser::OC_PropertyExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PropertyExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PropertyExpressionContext* CypherParser::oC_PropertyExpression() {
  OC_PropertyExpressionContext *_localctx = _tracker.createInstance<OC_PropertyExpressionContext>(_ctx, getState());
  enterRule(_localctx, 102, CypherParser::RuleOC_PropertyExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(914);
    oC_Atom();
    setState(919); 
    _errHandler->sync(this);
    alt = 1;
    do {
      switch (alt) {
        case 1: {
              setState(916);
              _errHandler->sync(this);

              _la = _input->LA(1);
              if (_la == CypherParser::SP) {
                setState(915);
                match(CypherParser::SP);
              }
              setState(918);
              oC_PropertyLookup();
              break;
            }

      default:
        throw NoViableAltException(this);
      }
      setState(921); 
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 156, _ctx);
    } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ExpressionContext ------------------------------------------------------------------

CypherParser::OC_ExpressionContext::OC_ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_OrExpressionContext* CypherParser::OC_ExpressionContext::oC_OrExpression() {
  return getRuleContext<CypherParser::OC_OrExpressionContext>(0);
}


size_t CypherParser::OC_ExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_Expression;
}

void CypherParser::OC_ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Expression(this);
}

void CypherParser::OC_ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Expression(this);
}


antlrcpp::Any CypherParser::OC_ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Expression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ExpressionContext* CypherParser::oC_Expression() {
  OC_ExpressionContext *_localctx = _tracker.createInstance<OC_ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 104, CypherParser::RuleOC_Expression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(923);
    oC_OrExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_OrExpressionContext ------------------------------------------------------------------

CypherParser::OC_OrExpressionContext::OC_OrExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_XorExpressionContext *> CypherParser::OC_OrExpressionContext::oC_XorExpression() {
  return getRuleContexts<CypherParser::OC_XorExpressionContext>();
}

CypherParser::OC_XorExpressionContext* CypherParser::OC_OrExpressionContext::oC_XorExpression(size_t i) {
  return getRuleContext<CypherParser::OC_XorExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_OrExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_OrExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_OrExpressionContext::OR() {
  return getTokens(CypherParser::OR);
}

tree::TerminalNode* CypherParser::OC_OrExpressionContext::OR(size_t i) {
  return getToken(CypherParser::OR, i);
}


size_t CypherParser::OC_OrExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_OrExpression;
}

void CypherParser::OC_OrExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_OrExpression(this);
}

void CypherParser::OC_OrExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_OrExpression(this);
}


antlrcpp::Any CypherParser::OC_OrExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_OrExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_OrExpressionContext* CypherParser::oC_OrExpression() {
  OC_OrExpressionContext *_localctx = _tracker.createInstance<OC_OrExpressionContext>(_ctx, getState());
  enterRule(_localctx, 106, CypherParser::RuleOC_OrExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(925);
    oC_XorExpression();
    setState(932);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 157, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(926);
        match(CypherParser::SP);
        setState(927);
        match(CypherParser::OR);
        setState(928);
        match(CypherParser::SP);
        setState(929);
        oC_XorExpression(); 
      }
      setState(934);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 157, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_XorExpressionContext ------------------------------------------------------------------

CypherParser::OC_XorExpressionContext::OC_XorExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_AndExpressionContext *> CypherParser::OC_XorExpressionContext::oC_AndExpression() {
  return getRuleContexts<CypherParser::OC_AndExpressionContext>();
}

CypherParser::OC_AndExpressionContext* CypherParser::OC_XorExpressionContext::oC_AndExpression(size_t i) {
  return getRuleContext<CypherParser::OC_AndExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_XorExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_XorExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_XorExpressionContext::XOR() {
  return getTokens(CypherParser::XOR);
}

tree::TerminalNode* CypherParser::OC_XorExpressionContext::XOR(size_t i) {
  return getToken(CypherParser::XOR, i);
}


size_t CypherParser::OC_XorExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_XorExpression;
}

void CypherParser::OC_XorExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_XorExpression(this);
}

void CypherParser::OC_XorExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_XorExpression(this);
}


antlrcpp::Any CypherParser::OC_XorExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_XorExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_XorExpressionContext* CypherParser::oC_XorExpression() {
  OC_XorExpressionContext *_localctx = _tracker.createInstance<OC_XorExpressionContext>(_ctx, getState());
  enterRule(_localctx, 108, CypherParser::RuleOC_XorExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(935);
    oC_AndExpression();
    setState(942);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 158, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(936);
        match(CypherParser::SP);
        setState(937);
        match(CypherParser::XOR);
        setState(938);
        match(CypherParser::SP);
        setState(939);
        oC_AndExpression(); 
      }
      setState(944);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 158, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_AndExpressionContext ------------------------------------------------------------------

CypherParser::OC_AndExpressionContext::OC_AndExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_NotExpressionContext *> CypherParser::OC_AndExpressionContext::oC_NotExpression() {
  return getRuleContexts<CypherParser::OC_NotExpressionContext>();
}

CypherParser::OC_NotExpressionContext* CypherParser::OC_AndExpressionContext::oC_NotExpression(size_t i) {
  return getRuleContext<CypherParser::OC_NotExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_AndExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_AndExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_AndExpressionContext::AND() {
  return getTokens(CypherParser::AND);
}

tree::TerminalNode* CypherParser::OC_AndExpressionContext::AND(size_t i) {
  return getToken(CypherParser::AND, i);
}


size_t CypherParser::OC_AndExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_AndExpression;
}

void CypherParser::OC_AndExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_AndExpression(this);
}

void CypherParser::OC_AndExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_AndExpression(this);
}


antlrcpp::Any CypherParser::OC_AndExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_AndExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_AndExpressionContext* CypherParser::oC_AndExpression() {
  OC_AndExpressionContext *_localctx = _tracker.createInstance<OC_AndExpressionContext>(_ctx, getState());
  enterRule(_localctx, 110, CypherParser::RuleOC_AndExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(945);
    oC_NotExpression();
    setState(952);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 159, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(946);
        match(CypherParser::SP);
        setState(947);
        match(CypherParser::AND);
        setState(948);
        match(CypherParser::SP);
        setState(949);
        oC_NotExpression(); 
      }
      setState(954);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 159, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NotExpressionContext ------------------------------------------------------------------

CypherParser::OC_NotExpressionContext::OC_NotExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ComparisonExpressionContext* CypherParser::OC_NotExpressionContext::oC_ComparisonExpression() {
  return getRuleContext<CypherParser::OC_ComparisonExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_NotExpressionContext::NOT() {
  return getTokens(CypherParser::NOT);
}

tree::TerminalNode* CypherParser::OC_NotExpressionContext::NOT(size_t i) {
  return getToken(CypherParser::NOT, i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_NotExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_NotExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_NotExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_NotExpression;
}

void CypherParser::OC_NotExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_NotExpression(this);
}

void CypherParser::OC_NotExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_NotExpression(this);
}


antlrcpp::Any CypherParser::OC_NotExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_NotExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NotExpressionContext* CypherParser::oC_NotExpression() {
  OC_NotExpressionContext *_localctx = _tracker.createInstance<OC_NotExpressionContext>(_ctx, getState());
  enterRule(_localctx, 112, CypherParser::RuleOC_NotExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(961);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 161, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(955);
        match(CypherParser::NOT);
        setState(957);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(956);
          match(CypherParser::SP);
        } 
      }
      setState(963);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 161, _ctx);
    }
    setState(964);
    oC_ComparisonExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ComparisonExpressionContext ------------------------------------------------------------------

CypherParser::OC_ComparisonExpressionContext::OC_ComparisonExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_StringListNullPredicateExpressionContext* CypherParser::OC_ComparisonExpressionContext::oC_StringListNullPredicateExpression() {
  return getRuleContext<CypherParser::OC_StringListNullPredicateExpressionContext>(0);
}

std::vector<CypherParser::OC_PartialComparisonExpressionContext *> CypherParser::OC_ComparisonExpressionContext::oC_PartialComparisonExpression() {
  return getRuleContexts<CypherParser::OC_PartialComparisonExpressionContext>();
}

CypherParser::OC_PartialComparisonExpressionContext* CypherParser::OC_ComparisonExpressionContext::oC_PartialComparisonExpression(size_t i) {
  return getRuleContext<CypherParser::OC_PartialComparisonExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ComparisonExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ComparisonExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_ComparisonExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_ComparisonExpression;
}

void CypherParser::OC_ComparisonExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ComparisonExpression(this);
}

void CypherParser::OC_ComparisonExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ComparisonExpression(this);
}


antlrcpp::Any CypherParser::OC_ComparisonExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ComparisonExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ComparisonExpressionContext* CypherParser::oC_ComparisonExpression() {
  OC_ComparisonExpressionContext *_localctx = _tracker.createInstance<OC_ComparisonExpressionContext>(_ctx, getState());
  enterRule(_localctx, 114, CypherParser::RuleOC_ComparisonExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(966);
    oC_StringListNullPredicateExpression();
    setState(973);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 163, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(968);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(967);
          match(CypherParser::SP);
        }
        setState(970);
        oC_PartialComparisonExpression(); 
      }
      setState(975);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 163, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PartialComparisonExpressionContext ------------------------------------------------------------------

CypherParser::OC_PartialComparisonExpressionContext::OC_PartialComparisonExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_StringListNullPredicateExpressionContext* CypherParser::OC_PartialComparisonExpressionContext::oC_StringListNullPredicateExpression() {
  return getRuleContext<CypherParser::OC_StringListNullPredicateExpressionContext>(0);
}

tree::TerminalNode* CypherParser::OC_PartialComparisonExpressionContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_PartialComparisonExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_PartialComparisonExpression;
}

void CypherParser::OC_PartialComparisonExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PartialComparisonExpression(this);
}

void CypherParser::OC_PartialComparisonExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PartialComparisonExpression(this);
}


antlrcpp::Any CypherParser::OC_PartialComparisonExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PartialComparisonExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PartialComparisonExpressionContext* CypherParser::oC_PartialComparisonExpression() {
  OC_PartialComparisonExpressionContext *_localctx = _tracker.createInstance<OC_PartialComparisonExpressionContext>(_ctx, getState());
  enterRule(_localctx, 116, CypherParser::RuleOC_PartialComparisonExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1006);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::T__2: {
        enterOuterAlt(_localctx, 1);
        setState(976);
        match(CypherParser::T__2);
        setState(978);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(977);
          match(CypherParser::SP);
        }
        setState(980);
        oC_StringListNullPredicateExpression();
        break;
      }

      case CypherParser::T__12: {
        enterOuterAlt(_localctx, 2);
        setState(981);
        match(CypherParser::T__12);
        setState(983);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(982);
          match(CypherParser::SP);
        }
        setState(985);
        oC_StringListNullPredicateExpression();
        break;
      }

      case CypherParser::T__13: {
        enterOuterAlt(_localctx, 3);
        setState(986);
        match(CypherParser::T__13);
        setState(988);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(987);
          match(CypherParser::SP);
        }
        setState(990);
        oC_StringListNullPredicateExpression();
        break;
      }

      case CypherParser::T__14: {
        enterOuterAlt(_localctx, 4);
        setState(991);
        match(CypherParser::T__14);
        setState(993);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(992);
          match(CypherParser::SP);
        }
        setState(995);
        oC_StringListNullPredicateExpression();
        break;
      }

      case CypherParser::T__15: {
        enterOuterAlt(_localctx, 5);
        setState(996);
        match(CypherParser::T__15);
        setState(998);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(997);
          match(CypherParser::SP);
        }
        setState(1000);
        oC_StringListNullPredicateExpression();
        break;
      }

      case CypherParser::T__16: {
        enterOuterAlt(_localctx, 6);
        setState(1001);
        match(CypherParser::T__16);
        setState(1003);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1002);
          match(CypherParser::SP);
        }
        setState(1005);
        oC_StringListNullPredicateExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_StringListNullPredicateExpressionContext ------------------------------------------------------------------

CypherParser::OC_StringListNullPredicateExpressionContext::OC_StringListNullPredicateExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_AddOrSubtractExpressionContext* CypherParser::OC_StringListNullPredicateExpressionContext::oC_AddOrSubtractExpression() {
  return getRuleContext<CypherParser::OC_AddOrSubtractExpressionContext>(0);
}

std::vector<CypherParser::OC_StringPredicateExpressionContext *> CypherParser::OC_StringListNullPredicateExpressionContext::oC_StringPredicateExpression() {
  return getRuleContexts<CypherParser::OC_StringPredicateExpressionContext>();
}

CypherParser::OC_StringPredicateExpressionContext* CypherParser::OC_StringListNullPredicateExpressionContext::oC_StringPredicateExpression(size_t i) {
  return getRuleContext<CypherParser::OC_StringPredicateExpressionContext>(i);
}

std::vector<CypherParser::OC_ListPredicateExpressionContext *> CypherParser::OC_StringListNullPredicateExpressionContext::oC_ListPredicateExpression() {
  return getRuleContexts<CypherParser::OC_ListPredicateExpressionContext>();
}

CypherParser::OC_ListPredicateExpressionContext* CypherParser::OC_StringListNullPredicateExpressionContext::oC_ListPredicateExpression(size_t i) {
  return getRuleContext<CypherParser::OC_ListPredicateExpressionContext>(i);
}

std::vector<CypherParser::OC_NullPredicateExpressionContext *> CypherParser::OC_StringListNullPredicateExpressionContext::oC_NullPredicateExpression() {
  return getRuleContexts<CypherParser::OC_NullPredicateExpressionContext>();
}

CypherParser::OC_NullPredicateExpressionContext* CypherParser::OC_StringListNullPredicateExpressionContext::oC_NullPredicateExpression(size_t i) {
  return getRuleContext<CypherParser::OC_NullPredicateExpressionContext>(i);
}


size_t CypherParser::OC_StringListNullPredicateExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_StringListNullPredicateExpression;
}

void CypherParser::OC_StringListNullPredicateExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_StringListNullPredicateExpression(this);
}

void CypherParser::OC_StringListNullPredicateExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_StringListNullPredicateExpression(this);
}


antlrcpp::Any CypherParser::OC_StringListNullPredicateExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_StringListNullPredicateExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_StringListNullPredicateExpressionContext* CypherParser::oC_StringListNullPredicateExpression() {
  OC_StringListNullPredicateExpressionContext *_localctx = _tracker.createInstance<OC_StringListNullPredicateExpressionContext>(_ctx, getState());
  enterRule(_localctx, 118, CypherParser::RuleOC_StringListNullPredicateExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1008);
    oC_AddOrSubtractExpression();
    setState(1014);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 172, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1012);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 171, _ctx)) {
        case 1: {
          setState(1009);
          oC_StringPredicateExpression();
          break;
        }

        case 2: {
          setState(1010);
          oC_ListPredicateExpression();
          break;
        }

        case 3: {
          setState(1011);
          oC_NullPredicateExpression();
          break;
        }

        } 
      }
      setState(1016);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 172, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_StringPredicateExpressionContext ------------------------------------------------------------------

CypherParser::OC_StringPredicateExpressionContext::OC_StringPredicateExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_AddOrSubtractExpressionContext* CypherParser::OC_StringPredicateExpressionContext::oC_AddOrSubtractExpression() {
  return getRuleContext<CypherParser::OC_AddOrSubtractExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_StringPredicateExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_StringPredicateExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_StringPredicateExpressionContext::STARTS() {
  return getToken(CypherParser::STARTS, 0);
}

tree::TerminalNode* CypherParser::OC_StringPredicateExpressionContext::WITH() {
  return getToken(CypherParser::WITH, 0);
}

tree::TerminalNode* CypherParser::OC_StringPredicateExpressionContext::ENDS() {
  return getToken(CypherParser::ENDS, 0);
}

tree::TerminalNode* CypherParser::OC_StringPredicateExpressionContext::CONTAINS() {
  return getToken(CypherParser::CONTAINS, 0);
}


size_t CypherParser::OC_StringPredicateExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_StringPredicateExpression;
}

void CypherParser::OC_StringPredicateExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_StringPredicateExpression(this);
}

void CypherParser::OC_StringPredicateExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_StringPredicateExpression(this);
}


antlrcpp::Any CypherParser::OC_StringPredicateExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_StringPredicateExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_StringPredicateExpressionContext* CypherParser::oC_StringPredicateExpression() {
  OC_StringPredicateExpressionContext *_localctx = _tracker.createInstance<OC_StringPredicateExpressionContext>(_ctx, getState());
  enterRule(_localctx, 120, CypherParser::RuleOC_StringPredicateExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1027);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 173, _ctx)) {
    case 1: {
      setState(1017);
      match(CypherParser::SP);
      setState(1018);
      match(CypherParser::STARTS);
      setState(1019);
      match(CypherParser::SP);
      setState(1020);
      match(CypherParser::WITH);
      break;
    }

    case 2: {
      setState(1021);
      match(CypherParser::SP);
      setState(1022);
      match(CypherParser::ENDS);
      setState(1023);
      match(CypherParser::SP);
      setState(1024);
      match(CypherParser::WITH);
      break;
    }

    case 3: {
      setState(1025);
      match(CypherParser::SP);
      setState(1026);
      match(CypherParser::CONTAINS);
      break;
    }

    }
    setState(1030);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1029);
      match(CypherParser::SP);
    }
    setState(1032);
    oC_AddOrSubtractExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ListPredicateExpressionContext ------------------------------------------------------------------

CypherParser::OC_ListPredicateExpressionContext::OC_ListPredicateExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_ListPredicateExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ListPredicateExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_ListPredicateExpressionContext::IN() {
  return getToken(CypherParser::IN, 0);
}

CypherParser::OC_AddOrSubtractExpressionContext* CypherParser::OC_ListPredicateExpressionContext::oC_AddOrSubtractExpression() {
  return getRuleContext<CypherParser::OC_AddOrSubtractExpressionContext>(0);
}


size_t CypherParser::OC_ListPredicateExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_ListPredicateExpression;
}

void CypherParser::OC_ListPredicateExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ListPredicateExpression(this);
}

void CypherParser::OC_ListPredicateExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ListPredicateExpression(this);
}


antlrcpp::Any CypherParser::OC_ListPredicateExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ListPredicateExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ListPredicateExpressionContext* CypherParser::oC_ListPredicateExpression() {
  OC_ListPredicateExpressionContext *_localctx = _tracker.createInstance<OC_ListPredicateExpressionContext>(_ctx, getState());
  enterRule(_localctx, 122, CypherParser::RuleOC_ListPredicateExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1034);
    match(CypherParser::SP);
    setState(1035);
    match(CypherParser::IN);
    setState(1037);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1036);
      match(CypherParser::SP);
    }
    setState(1039);
    oC_AddOrSubtractExpression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NullPredicateExpressionContext ------------------------------------------------------------------

CypherParser::OC_NullPredicateExpressionContext::OC_NullPredicateExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_NullPredicateExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_NullPredicateExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_NullPredicateExpressionContext::IS() {
  return getToken(CypherParser::IS, 0);
}

tree::TerminalNode* CypherParser::OC_NullPredicateExpressionContext::CypherNULL() {
  return getToken(CypherParser::CypherNULL, 0);
}

tree::TerminalNode* CypherParser::OC_NullPredicateExpressionContext::NOT() {
  return getToken(CypherParser::NOT, 0);
}


size_t CypherParser::OC_NullPredicateExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_NullPredicateExpression;
}

void CypherParser::OC_NullPredicateExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_NullPredicateExpression(this);
}

void CypherParser::OC_NullPredicateExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_NullPredicateExpression(this);
}


antlrcpp::Any CypherParser::OC_NullPredicateExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_NullPredicateExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NullPredicateExpressionContext* CypherParser::oC_NullPredicateExpression() {
  OC_NullPredicateExpressionContext *_localctx = _tracker.createInstance<OC_NullPredicateExpressionContext>(_ctx, getState());
  enterRule(_localctx, 124, CypherParser::RuleOC_NullPredicateExpression);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1051);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 176, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1041);
      match(CypherParser::SP);
      setState(1042);
      match(CypherParser::IS);
      setState(1043);
      match(CypherParser::SP);
      setState(1044);
      match(CypherParser::CypherNULL);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1045);
      match(CypherParser::SP);
      setState(1046);
      match(CypherParser::IS);
      setState(1047);
      match(CypherParser::SP);
      setState(1048);
      match(CypherParser::NOT);
      setState(1049);
      match(CypherParser::SP);
      setState(1050);
      match(CypherParser::CypherNULL);
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_AddOrSubtractExpressionContext ------------------------------------------------------------------

CypherParser::OC_AddOrSubtractExpressionContext::OC_AddOrSubtractExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_MultiplyDivideModuloExpressionContext *> CypherParser::OC_AddOrSubtractExpressionContext::oC_MultiplyDivideModuloExpression() {
  return getRuleContexts<CypherParser::OC_MultiplyDivideModuloExpressionContext>();
}

CypherParser::OC_MultiplyDivideModuloExpressionContext* CypherParser::OC_AddOrSubtractExpressionContext::oC_MultiplyDivideModuloExpression(size_t i) {
  return getRuleContext<CypherParser::OC_MultiplyDivideModuloExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_AddOrSubtractExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_AddOrSubtractExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_AddOrSubtractExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_AddOrSubtractExpression;
}

void CypherParser::OC_AddOrSubtractExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_AddOrSubtractExpression(this);
}

void CypherParser::OC_AddOrSubtractExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_AddOrSubtractExpression(this);
}


antlrcpp::Any CypherParser::OC_AddOrSubtractExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_AddOrSubtractExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_AddOrSubtractExpressionContext* CypherParser::oC_AddOrSubtractExpression() {
  OC_AddOrSubtractExpressionContext *_localctx = _tracker.createInstance<OC_AddOrSubtractExpressionContext>(_ctx, getState());
  enterRule(_localctx, 126, CypherParser::RuleOC_AddOrSubtractExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1053);
    oC_MultiplyDivideModuloExpression();
    setState(1072);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 182, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1070);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 181, _ctx)) {
        case 1: {
          setState(1055);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1054);
            match(CypherParser::SP);
          }
          setState(1057);
          match(CypherParser::T__17);
          setState(1059);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1058);
            match(CypherParser::SP);
          }
          setState(1061);
          oC_MultiplyDivideModuloExpression();
          break;
        }

        case 2: {
          setState(1063);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1062);
            match(CypherParser::SP);
          }
          setState(1065);
          match(CypherParser::T__18);
          setState(1067);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1066);
            match(CypherParser::SP);
          }
          setState(1069);
          oC_MultiplyDivideModuloExpression();
          break;
        }

        } 
      }
      setState(1074);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 182, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_MultiplyDivideModuloExpressionContext ------------------------------------------------------------------

CypherParser::OC_MultiplyDivideModuloExpressionContext::OC_MultiplyDivideModuloExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_PowerOfExpressionContext *> CypherParser::OC_MultiplyDivideModuloExpressionContext::oC_PowerOfExpression() {
  return getRuleContexts<CypherParser::OC_PowerOfExpressionContext>();
}

CypherParser::OC_PowerOfExpressionContext* CypherParser::OC_MultiplyDivideModuloExpressionContext::oC_PowerOfExpression(size_t i) {
  return getRuleContext<CypherParser::OC_PowerOfExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_MultiplyDivideModuloExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_MultiplyDivideModuloExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_MultiplyDivideModuloExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_MultiplyDivideModuloExpression;
}

void CypherParser::OC_MultiplyDivideModuloExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_MultiplyDivideModuloExpression(this);
}

void CypherParser::OC_MultiplyDivideModuloExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_MultiplyDivideModuloExpression(this);
}


antlrcpp::Any CypherParser::OC_MultiplyDivideModuloExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_MultiplyDivideModuloExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_MultiplyDivideModuloExpressionContext* CypherParser::oC_MultiplyDivideModuloExpression() {
  OC_MultiplyDivideModuloExpressionContext *_localctx = _tracker.createInstance<OC_MultiplyDivideModuloExpressionContext>(_ctx, getState());
  enterRule(_localctx, 128, CypherParser::RuleOC_MultiplyDivideModuloExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1075);
    oC_PowerOfExpression();
    setState(1102);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 190, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1100);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 189, _ctx)) {
        case 1: {
          setState(1077);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1076);
            match(CypherParser::SP);
          }
          setState(1079);
          match(CypherParser::T__4);
          setState(1081);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1080);
            match(CypherParser::SP);
          }
          setState(1083);
          oC_PowerOfExpression();
          break;
        }

        case 2: {
          setState(1085);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1084);
            match(CypherParser::SP);
          }
          setState(1087);
          match(CypherParser::T__19);
          setState(1089);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1088);
            match(CypherParser::SP);
          }
          setState(1091);
          oC_PowerOfExpression();
          break;
        }

        case 3: {
          setState(1093);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1092);
            match(CypherParser::SP);
          }
          setState(1095);
          match(CypherParser::T__20);
          setState(1097);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1096);
            match(CypherParser::SP);
          }
          setState(1099);
          oC_PowerOfExpression();
          break;
        }

        } 
      }
      setState(1104);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 190, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PowerOfExpressionContext ------------------------------------------------------------------

CypherParser::OC_PowerOfExpressionContext::OC_PowerOfExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_UnaryAddOrSubtractExpressionContext *> CypherParser::OC_PowerOfExpressionContext::oC_UnaryAddOrSubtractExpression() {
  return getRuleContexts<CypherParser::OC_UnaryAddOrSubtractExpressionContext>();
}

CypherParser::OC_UnaryAddOrSubtractExpressionContext* CypherParser::OC_PowerOfExpressionContext::oC_UnaryAddOrSubtractExpression(size_t i) {
  return getRuleContext<CypherParser::OC_UnaryAddOrSubtractExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PowerOfExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PowerOfExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_PowerOfExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_PowerOfExpression;
}

void CypherParser::OC_PowerOfExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PowerOfExpression(this);
}

void CypherParser::OC_PowerOfExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PowerOfExpression(this);
}


antlrcpp::Any CypherParser::OC_PowerOfExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PowerOfExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PowerOfExpressionContext* CypherParser::oC_PowerOfExpression() {
  OC_PowerOfExpressionContext *_localctx = _tracker.createInstance<OC_PowerOfExpressionContext>(_ctx, getState());
  enterRule(_localctx, 130, CypherParser::RuleOC_PowerOfExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1105);
    oC_UnaryAddOrSubtractExpression();
    setState(1116);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 193, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1107);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1106);
          match(CypherParser::SP);
        }
        setState(1109);
        match(CypherParser::T__21);
        setState(1111);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1110);
          match(CypherParser::SP);
        }
        setState(1113);
        oC_UnaryAddOrSubtractExpression(); 
      }
      setState(1118);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 193, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_UnaryAddOrSubtractExpressionContext ------------------------------------------------------------------

CypherParser::OC_UnaryAddOrSubtractExpressionContext::OC_UnaryAddOrSubtractExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ListOperatorExpressionContext* CypherParser::OC_UnaryAddOrSubtractExpressionContext::oC_ListOperatorExpression() {
  return getRuleContext<CypherParser::OC_ListOperatorExpressionContext>(0);
}

tree::TerminalNode* CypherParser::OC_UnaryAddOrSubtractExpressionContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_UnaryAddOrSubtractExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_UnaryAddOrSubtractExpression;
}

void CypherParser::OC_UnaryAddOrSubtractExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_UnaryAddOrSubtractExpression(this);
}

void CypherParser::OC_UnaryAddOrSubtractExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_UnaryAddOrSubtractExpression(this);
}


antlrcpp::Any CypherParser::OC_UnaryAddOrSubtractExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_UnaryAddOrSubtractExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_UnaryAddOrSubtractExpressionContext* CypherParser::oC_UnaryAddOrSubtractExpression() {
  OC_UnaryAddOrSubtractExpressionContext *_localctx = _tracker.createInstance<OC_UnaryAddOrSubtractExpressionContext>(_ctx, getState());
  enterRule(_localctx, 132, CypherParser::RuleOC_UnaryAddOrSubtractExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1125);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::T__5:
      case CypherParser::T__7:
      case CypherParser::T__23:
      case CypherParser::T__25:
      case CypherParser::UNION:
      case CypherParser::ALL:
      case CypherParser::OPTIONAL:
      case CypherParser::MATCH:
      case CypherParser::UNWIND:
      case CypherParser::AS:
      case CypherParser::MERGE:
      case CypherParser::ON:
      case CypherParser::CREATE:
      case CypherParser::SET:
      case CypherParser::DETACH:
      case CypherParser::DELETE:
      case CypherParser::REMOVE:
      case CypherParser::WITH:
      case CypherParser::RETURN:
      case CypherParser::DISTINCT:
      case CypherParser::ORDER:
      case CypherParser::BY:
      case CypherParser::L_SKIP:
      case CypherParser::LIMIT:
      case CypherParser::ASCENDING:
      case CypherParser::ASC:
      case CypherParser::DESCENDING:
      case CypherParser::DESC:
      case CypherParser::WHERE:
      case CypherParser::OR:
      case CypherParser::XOR:
      case CypherParser::AND:
      case CypherParser::NOT:
      case CypherParser::STARTS:
      case CypherParser::ENDS:
      case CypherParser::CONTAINS:
      case CypherParser::IN:
      case CypherParser::IS:
      case CypherParser::CypherNULL:
      case CypherParser::COUNT:
      case CypherParser::CASE:
      case CypherParser::ELSE:
      case CypherParser::END:
      case CypherParser::WHEN:
      case CypherParser::THEN:
      case CypherParser::ANY:
      case CypherParser::NONE:
      case CypherParser::SINGLE:
      case CypherParser::EXISTS:
      case CypherParser::TRUE:
      case CypherParser::FALSE:
      case CypherParser::HexInteger:
      case CypherParser::DecimalInteger:
      case CypherParser::OctalInteger:
      case CypherParser::HexLetter:
      case CypherParser::ExponentDecimalReal:
      case CypherParser::RegularDecimalReal:
      case CypherParser::StringLiteral:
      case CypherParser::CONSTRAINT:
      case CypherParser::DO:
      case CypherParser::FOR:
      case CypherParser::REQUIRE:
      case CypherParser::UNIQUE:
      case CypherParser::MANDATORY:
      case CypherParser::SCALAR:
      case CypherParser::OF:
      case CypherParser::ADD:
      case CypherParser::DROP:
      case CypherParser::FILTER:
      case CypherParser::EXTRACT:
      case CypherParser::UnescapedSymbolicName:
      case CypherParser::EscapedSymbolicName: {
        enterOuterAlt(_localctx, 1);
        setState(1119);
        oC_ListOperatorExpression();
        break;
      }

      case CypherParser::T__17:
      case CypherParser::T__18: {
        enterOuterAlt(_localctx, 2);
        setState(1120);
        _la = _input->LA(1);
        if (!(_la == CypherParser::T__17

        || _la == CypherParser::T__18)) {
        _errHandler->recoverInline(this);
        }
        else {
          _errHandler->reportMatch(this);
          consume();
        }
        setState(1122);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1121);
          match(CypherParser::SP);
        }
        setState(1124);
        oC_ListOperatorExpression();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ListOperatorExpressionContext ------------------------------------------------------------------

CypherParser::OC_ListOperatorExpressionContext::OC_ListOperatorExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_PropertyOrLabelsExpressionContext* CypherParser::OC_ListOperatorExpressionContext::oC_PropertyOrLabelsExpression() {
  return getRuleContext<CypherParser::OC_PropertyOrLabelsExpressionContext>(0);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_ListOperatorExpressionContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_ListOperatorExpressionContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ListOperatorExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ListOperatorExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_ListOperatorExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_ListOperatorExpression;
}

void CypherParser::OC_ListOperatorExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ListOperatorExpression(this);
}

void CypherParser::OC_ListOperatorExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ListOperatorExpression(this);
}


antlrcpp::Any CypherParser::OC_ListOperatorExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ListOperatorExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ListOperatorExpressionContext* CypherParser::oC_ListOperatorExpression() {
  OC_ListOperatorExpressionContext *_localctx = _tracker.createInstance<OC_ListOperatorExpressionContext>(_ctx, getState());
  enterRule(_localctx, 134, CypherParser::RuleOC_ListOperatorExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1127);
    oC_PropertyOrLabelsExpression();
    setState(1149);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 201, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1147);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 200, _ctx)) {
        case 1: {
          setState(1129);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1128);
            match(CypherParser::SP);
          }
          setState(1131);
          match(CypherParser::T__7);
          setState(1132);
          oC_Expression();
          setState(1133);
          match(CypherParser::T__8);
          break;
        }

        case 2: {
          setState(1136);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1135);
            match(CypherParser::SP);
          }
          setState(1138);
          match(CypherParser::T__7);
          setState(1140);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << CypherParser::T__5)
            | (1ULL << CypherParser::T__7)
            | (1ULL << CypherParser::T__17)
            | (1ULL << CypherParser::T__18)
            | (1ULL << CypherParser::T__23)
            | (1ULL << CypherParser::T__25)
            | (1ULL << CypherParser::UNION)
            | (1ULL << CypherParser::ALL)
            | (1ULL << CypherParser::OPTIONAL)
            | (1ULL << CypherParser::MATCH)
            | (1ULL << CypherParser::UNWIND)
            | (1ULL << CypherParser::AS)
            | (1ULL << CypherParser::MERGE)
            | (1ULL << CypherParser::ON)
            | (1ULL << CypherParser::CREATE)
            | (1ULL << CypherParser::SET)
            | (1ULL << CypherParser::DETACH)
            | (1ULL << CypherParser::DELETE)
            | (1ULL << CypherParser::REMOVE)
            | (1ULL << CypherParser::WITH)
            | (1ULL << CypherParser::RETURN)
            | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
            | (1ULL << (CypherParser::BY - 64))
            | (1ULL << (CypherParser::L_SKIP - 64))
            | (1ULL << (CypherParser::LIMIT - 64))
            | (1ULL << (CypherParser::ASCENDING - 64))
            | (1ULL << (CypherParser::ASC - 64))
            | (1ULL << (CypherParser::DESCENDING - 64))
            | (1ULL << (CypherParser::DESC - 64))
            | (1ULL << (CypherParser::WHERE - 64))
            | (1ULL << (CypherParser::OR - 64))
            | (1ULL << (CypherParser::XOR - 64))
            | (1ULL << (CypherParser::AND - 64))
            | (1ULL << (CypherParser::NOT - 64))
            | (1ULL << (CypherParser::STARTS - 64))
            | (1ULL << (CypherParser::ENDS - 64))
            | (1ULL << (CypherParser::CONTAINS - 64))
            | (1ULL << (CypherParser::IN - 64))
            | (1ULL << (CypherParser::IS - 64))
            | (1ULL << (CypherParser::CypherNULL - 64))
            | (1ULL << (CypherParser::COUNT - 64))
            | (1ULL << (CypherParser::CASE - 64))
            | (1ULL << (CypherParser::ELSE - 64))
            | (1ULL << (CypherParser::END - 64))
            | (1ULL << (CypherParser::WHEN - 64))
            | (1ULL << (CypherParser::THEN - 64))
            | (1ULL << (CypherParser::ANY - 64))
            | (1ULL << (CypherParser::NONE - 64))
            | (1ULL << (CypherParser::SINGLE - 64))
            | (1ULL << (CypherParser::EXISTS - 64))
            | (1ULL << (CypherParser::TRUE - 64))
            | (1ULL << (CypherParser::FALSE - 64))
            | (1ULL << (CypherParser::HexInteger - 64))
            | (1ULL << (CypherParser::DecimalInteger - 64))
            | (1ULL << (CypherParser::OctalInteger - 64))
            | (1ULL << (CypherParser::HexLetter - 64))
            | (1ULL << (CypherParser::ExponentDecimalReal - 64))
            | (1ULL << (CypherParser::RegularDecimalReal - 64))
            | (1ULL << (CypherParser::StringLiteral - 64))
            | (1ULL << (CypherParser::CONSTRAINT - 64))
            | (1ULL << (CypherParser::DO - 64))
            | (1ULL << (CypherParser::FOR - 64))
            | (1ULL << (CypherParser::REQUIRE - 64))
            | (1ULL << (CypherParser::UNIQUE - 64))
            | (1ULL << (CypherParser::MANDATORY - 64))
            | (1ULL << (CypherParser::SCALAR - 64))
            | (1ULL << (CypherParser::OF - 64))
            | (1ULL << (CypherParser::ADD - 64))
            | (1ULL << (CypherParser::DROP - 64))
            | (1ULL << (CypherParser::FILTER - 64))
            | (1ULL << (CypherParser::EXTRACT - 64))
            | (1ULL << (CypherParser::UnescapedSymbolicName - 64))
            | (1ULL << (CypherParser::EscapedSymbolicName - 64)))) != 0)) {
            setState(1139);
            oC_Expression();
          }
          setState(1142);
          match(CypherParser::T__11);
          setState(1144);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if ((((_la & ~ 0x3fULL) == 0) &&
            ((1ULL << _la) & ((1ULL << CypherParser::T__5)
            | (1ULL << CypherParser::T__7)
            | (1ULL << CypherParser::T__17)
            | (1ULL << CypherParser::T__18)
            | (1ULL << CypherParser::T__23)
            | (1ULL << CypherParser::T__25)
            | (1ULL << CypherParser::UNION)
            | (1ULL << CypherParser::ALL)
            | (1ULL << CypherParser::OPTIONAL)
            | (1ULL << CypherParser::MATCH)
            | (1ULL << CypherParser::UNWIND)
            | (1ULL << CypherParser::AS)
            | (1ULL << CypherParser::MERGE)
            | (1ULL << CypherParser::ON)
            | (1ULL << CypherParser::CREATE)
            | (1ULL << CypherParser::SET)
            | (1ULL << CypherParser::DETACH)
            | (1ULL << CypherParser::DELETE)
            | (1ULL << CypherParser::REMOVE)
            | (1ULL << CypherParser::WITH)
            | (1ULL << CypherParser::RETURN)
            | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
            ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
            | (1ULL << (CypherParser::BY - 64))
            | (1ULL << (CypherParser::L_SKIP - 64))
            | (1ULL << (CypherParser::LIMIT - 64))
            | (1ULL << (CypherParser::ASCENDING - 64))
            | (1ULL << (CypherParser::ASC - 64))
            | (1ULL << (CypherParser::DESCENDING - 64))
            | (1ULL << (CypherParser::DESC - 64))
            | (1ULL << (CypherParser::WHERE - 64))
            | (1ULL << (CypherParser::OR - 64))
            | (1ULL << (CypherParser::XOR - 64))
            | (1ULL << (CypherParser::AND - 64))
            | (1ULL << (CypherParser::NOT - 64))
            | (1ULL << (CypherParser::STARTS - 64))
            | (1ULL << (CypherParser::ENDS - 64))
            | (1ULL << (CypherParser::CONTAINS - 64))
            | (1ULL << (CypherParser::IN - 64))
            | (1ULL << (CypherParser::IS - 64))
            | (1ULL << (CypherParser::CypherNULL - 64))
            | (1ULL << (CypherParser::COUNT - 64))
            | (1ULL << (CypherParser::CASE - 64))
            | (1ULL << (CypherParser::ELSE - 64))
            | (1ULL << (CypherParser::END - 64))
            | (1ULL << (CypherParser::WHEN - 64))
            | (1ULL << (CypherParser::THEN - 64))
            | (1ULL << (CypherParser::ANY - 64))
            | (1ULL << (CypherParser::NONE - 64))
            | (1ULL << (CypherParser::SINGLE - 64))
            | (1ULL << (CypherParser::EXISTS - 64))
            | (1ULL << (CypherParser::TRUE - 64))
            | (1ULL << (CypherParser::FALSE - 64))
            | (1ULL << (CypherParser::HexInteger - 64))
            | (1ULL << (CypherParser::DecimalInteger - 64))
            | (1ULL << (CypherParser::OctalInteger - 64))
            | (1ULL << (CypherParser::HexLetter - 64))
            | (1ULL << (CypherParser::ExponentDecimalReal - 64))
            | (1ULL << (CypherParser::RegularDecimalReal - 64))
            | (1ULL << (CypherParser::StringLiteral - 64))
            | (1ULL << (CypherParser::CONSTRAINT - 64))
            | (1ULL << (CypherParser::DO - 64))
            | (1ULL << (CypherParser::FOR - 64))
            | (1ULL << (CypherParser::REQUIRE - 64))
            | (1ULL << (CypherParser::UNIQUE - 64))
            | (1ULL << (CypherParser::MANDATORY - 64))
            | (1ULL << (CypherParser::SCALAR - 64))
            | (1ULL << (CypherParser::OF - 64))
            | (1ULL << (CypherParser::ADD - 64))
            | (1ULL << (CypherParser::DROP - 64))
            | (1ULL << (CypherParser::FILTER - 64))
            | (1ULL << (CypherParser::EXTRACT - 64))
            | (1ULL << (CypherParser::UnescapedSymbolicName - 64))
            | (1ULL << (CypherParser::EscapedSymbolicName - 64)))) != 0)) {
            setState(1143);
            oC_Expression();
          }
          setState(1146);
          match(CypherParser::T__8);
          break;
        }

        } 
      }
      setState(1151);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 201, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PropertyOrLabelsExpressionContext ------------------------------------------------------------------

CypherParser::OC_PropertyOrLabelsExpressionContext::OC_PropertyOrLabelsExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_AtomContext* CypherParser::OC_PropertyOrLabelsExpressionContext::oC_Atom() {
  return getRuleContext<CypherParser::OC_AtomContext>(0);
}

std::vector<CypherParser::OC_PropertyLookupContext *> CypherParser::OC_PropertyOrLabelsExpressionContext::oC_PropertyLookup() {
  return getRuleContexts<CypherParser::OC_PropertyLookupContext>();
}

CypherParser::OC_PropertyLookupContext* CypherParser::OC_PropertyOrLabelsExpressionContext::oC_PropertyLookup(size_t i) {
  return getRuleContext<CypherParser::OC_PropertyLookupContext>(i);
}

CypherParser::OC_NodeLabelsContext* CypherParser::OC_PropertyOrLabelsExpressionContext::oC_NodeLabels() {
  return getRuleContext<CypherParser::OC_NodeLabelsContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PropertyOrLabelsExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PropertyOrLabelsExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_PropertyOrLabelsExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_PropertyOrLabelsExpression;
}

void CypherParser::OC_PropertyOrLabelsExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PropertyOrLabelsExpression(this);
}

void CypherParser::OC_PropertyOrLabelsExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PropertyOrLabelsExpression(this);
}


antlrcpp::Any CypherParser::OC_PropertyOrLabelsExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PropertyOrLabelsExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PropertyOrLabelsExpressionContext* CypherParser::oC_PropertyOrLabelsExpression() {
  OC_PropertyOrLabelsExpressionContext *_localctx = _tracker.createInstance<OC_PropertyOrLabelsExpressionContext>(_ctx, getState());
  enterRule(_localctx, 136, CypherParser::RuleOC_PropertyOrLabelsExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1152);
    oC_Atom();
    setState(1159);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 203, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1154);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1153);
          match(CypherParser::SP);
        }
        setState(1156);
        oC_PropertyLookup(); 
      }
      setState(1161);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 203, _ctx);
    }
    setState(1166);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 205, _ctx)) {
    case 1: {
      setState(1163);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1162);
        match(CypherParser::SP);
      }
      setState(1165);
      oC_NodeLabels();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PropertyLookupContext ------------------------------------------------------------------

CypherParser::OC_PropertyLookupContext::OC_PropertyLookupContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_PropertyKeyNameContext* CypherParser::OC_PropertyLookupContext::oC_PropertyKeyName() {
  return getRuleContext<CypherParser::OC_PropertyKeyNameContext>(0);
}

tree::TerminalNode* CypherParser::OC_PropertyLookupContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_PropertyLookupContext::getRuleIndex() const {
  return CypherParser::RuleOC_PropertyLookup;
}

void CypherParser::OC_PropertyLookupContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PropertyLookup(this);
}

void CypherParser::OC_PropertyLookupContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PropertyLookup(this);
}


antlrcpp::Any CypherParser::OC_PropertyLookupContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PropertyLookup(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PropertyLookupContext* CypherParser::oC_PropertyLookup() {
  OC_PropertyLookupContext *_localctx = _tracker.createInstance<OC_PropertyLookupContext>(_ctx, getState());
  enterRule(_localctx, 138, CypherParser::RuleOC_PropertyLookup);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1168);
    match(CypherParser::T__22);
    setState(1170);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1169);
      match(CypherParser::SP);
    }

    setState(1172);
    oC_PropertyKeyName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_AtomContext ------------------------------------------------------------------

CypherParser::OC_AtomContext::OC_AtomContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_LiteralContext* CypherParser::OC_AtomContext::oC_Literal() {
  return getRuleContext<CypherParser::OC_LiteralContext>(0);
}

CypherParser::OC_ParameterContext* CypherParser::OC_AtomContext::oC_Parameter() {
  return getRuleContext<CypherParser::OC_ParameterContext>(0);
}

CypherParser::OC_CaseExpressionContext* CypherParser::OC_AtomContext::oC_CaseExpression() {
  return getRuleContext<CypherParser::OC_CaseExpressionContext>(0);
}

tree::TerminalNode* CypherParser::OC_AtomContext::COUNT() {
  return getToken(CypherParser::COUNT, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_AtomContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_AtomContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_ListComprehensionContext* CypherParser::OC_AtomContext::oC_ListComprehension() {
  return getRuleContext<CypherParser::OC_ListComprehensionContext>(0);
}

CypherParser::OC_PatternComprehensionContext* CypherParser::OC_AtomContext::oC_PatternComprehension() {
  return getRuleContext<CypherParser::OC_PatternComprehensionContext>(0);
}

CypherParser::OC_QuantifierContext* CypherParser::OC_AtomContext::oC_Quantifier() {
  return getRuleContext<CypherParser::OC_QuantifierContext>(0);
}

CypherParser::OC_PatternPredicateContext* CypherParser::OC_AtomContext::oC_PatternPredicate() {
  return getRuleContext<CypherParser::OC_PatternPredicateContext>(0);
}

CypherParser::OC_ParenthesizedExpressionContext* CypherParser::OC_AtomContext::oC_ParenthesizedExpression() {
  return getRuleContext<CypherParser::OC_ParenthesizedExpressionContext>(0);
}

CypherParser::OC_FunctionInvocationContext* CypherParser::OC_AtomContext::oC_FunctionInvocation() {
  return getRuleContext<CypherParser::OC_FunctionInvocationContext>(0);
}

CypherParser::OC_ExistentialSubqueryContext* CypherParser::OC_AtomContext::oC_ExistentialSubquery() {
  return getRuleContext<CypherParser::OC_ExistentialSubqueryContext>(0);
}

CypherParser::OC_VariableContext* CypherParser::OC_AtomContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}


size_t CypherParser::OC_AtomContext::getRuleIndex() const {
  return CypherParser::RuleOC_Atom;
}

void CypherParser::OC_AtomContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Atom(this);
}

void CypherParser::OC_AtomContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Atom(this);
}


antlrcpp::Any CypherParser::OC_AtomContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Atom(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_AtomContext* CypherParser::oC_Atom() {
  OC_AtomContext *_localctx = _tracker.createInstance<OC_AtomContext>(_ctx, getState());
  enterRule(_localctx, 140, CypherParser::RuleOC_Atom);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1198);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 210, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(1174);
      oC_Literal();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(1175);
      oC_Parameter();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(1176);
      oC_CaseExpression();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(1177);
      match(CypherParser::COUNT);
      setState(1179);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1178);
        match(CypherParser::SP);
      }
      setState(1181);
      match(CypherParser::T__5);
      setState(1183);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1182);
        match(CypherParser::SP);
      }
      setState(1185);
      match(CypherParser::T__4);
      setState(1187);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1186);
        match(CypherParser::SP);
      }
      setState(1189);
      match(CypherParser::T__6);
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(1190);
      oC_ListComprehension();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(1191);
      oC_PatternComprehension();
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(1192);
      oC_Quantifier();
      break;
    }

    case 8: {
      enterOuterAlt(_localctx, 8);
      setState(1193);
      oC_PatternPredicate();
      break;
    }

    case 9: {
      enterOuterAlt(_localctx, 9);
      setState(1194);
      oC_ParenthesizedExpression();
      break;
    }

    case 10: {
      enterOuterAlt(_localctx, 10);
      setState(1195);
      oC_FunctionInvocation();
      break;
    }

    case 11: {
      enterOuterAlt(_localctx, 11);
      setState(1196);
      oC_ExistentialSubquery();
      break;
    }

    case 12: {
      enterOuterAlt(_localctx, 12);
      setState(1197);
      oC_Variable();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_CaseExpressionContext ------------------------------------------------------------------

CypherParser::OC_CaseExpressionContext::OC_CaseExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_CaseExpressionContext::END() {
  return getToken(CypherParser::END, 0);
}

tree::TerminalNode* CypherParser::OC_CaseExpressionContext::ELSE() {
  return getToken(CypherParser::ELSE, 0);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_CaseExpressionContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_CaseExpressionContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}

std::vector<tree::TerminalNode *> CypherParser::OC_CaseExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_CaseExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_CaseExpressionContext::CASE() {
  return getToken(CypherParser::CASE, 0);
}

std::vector<CypherParser::OC_CaseAlternativeContext *> CypherParser::OC_CaseExpressionContext::oC_CaseAlternative() {
  return getRuleContexts<CypherParser::OC_CaseAlternativeContext>();
}

CypherParser::OC_CaseAlternativeContext* CypherParser::OC_CaseExpressionContext::oC_CaseAlternative(size_t i) {
  return getRuleContext<CypherParser::OC_CaseAlternativeContext>(i);
}


size_t CypherParser::OC_CaseExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_CaseExpression;
}

void CypherParser::OC_CaseExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_CaseExpression(this);
}

void CypherParser::OC_CaseExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_CaseExpression(this);
}


antlrcpp::Any CypherParser::OC_CaseExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_CaseExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_CaseExpressionContext* CypherParser::oC_CaseExpression() {
  OC_CaseExpressionContext *_localctx = _tracker.createInstance<OC_CaseExpressionContext>(_ctx, getState());
  enterRule(_localctx, 142, CypherParser::RuleOC_CaseExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1222);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 216, _ctx)) {
    case 1: {
      setState(1200);
      match(CypherParser::CASE);
      setState(1205); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(1202);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == CypherParser::SP) {
                  setState(1201);
                  match(CypherParser::SP);
                }
                setState(1204);
                oC_CaseAlternative();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(1207); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 212, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    case 2: {
      setState(1209);
      match(CypherParser::CASE);
      setState(1211);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1210);
        match(CypherParser::SP);
      }
      setState(1213);
      oC_Expression();
      setState(1218); 
      _errHandler->sync(this);
      alt = 1;
      do {
        switch (alt) {
          case 1: {
                setState(1215);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if (_la == CypherParser::SP) {
                  setState(1214);
                  match(CypherParser::SP);
                }
                setState(1217);
                oC_CaseAlternative();
                break;
              }

        default:
          throw NoViableAltException(this);
        }
        setState(1220); 
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 215, _ctx);
      } while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER);
      break;
    }

    }
    setState(1232);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 219, _ctx)) {
    case 1: {
      setState(1225);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1224);
        match(CypherParser::SP);
      }
      setState(1227);
      match(CypherParser::ELSE);
      setState(1229);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1228);
        match(CypherParser::SP);
      }
      setState(1231);
      oC_Expression();
      break;
    }

    }
    setState(1235);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1234);
      match(CypherParser::SP);
    }
    setState(1237);
    match(CypherParser::END);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_CaseAlternativeContext ------------------------------------------------------------------

CypherParser::OC_CaseAlternativeContext::OC_CaseAlternativeContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_CaseAlternativeContext::WHEN() {
  return getToken(CypherParser::WHEN, 0);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_CaseAlternativeContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_CaseAlternativeContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}

tree::TerminalNode* CypherParser::OC_CaseAlternativeContext::THEN() {
  return getToken(CypherParser::THEN, 0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_CaseAlternativeContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_CaseAlternativeContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_CaseAlternativeContext::getRuleIndex() const {
  return CypherParser::RuleOC_CaseAlternative;
}

void CypherParser::OC_CaseAlternativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_CaseAlternative(this);
}

void CypherParser::OC_CaseAlternativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_CaseAlternative(this);
}


antlrcpp::Any CypherParser::OC_CaseAlternativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_CaseAlternative(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_CaseAlternativeContext* CypherParser::oC_CaseAlternative() {
  OC_CaseAlternativeContext *_localctx = _tracker.createInstance<OC_CaseAlternativeContext>(_ctx, getState());
  enterRule(_localctx, 144, CypherParser::RuleOC_CaseAlternative);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1239);
    match(CypherParser::WHEN);
    setState(1241);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1240);
      match(CypherParser::SP);
    }
    setState(1243);
    oC_Expression();
    setState(1245);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1244);
      match(CypherParser::SP);
    }
    setState(1247);
    match(CypherParser::THEN);
    setState(1249);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1248);
      match(CypherParser::SP);
    }
    setState(1251);
    oC_Expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ListComprehensionContext ------------------------------------------------------------------

CypherParser::OC_ListComprehensionContext::OC_ListComprehensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_FilterExpressionContext* CypherParser::OC_ListComprehensionContext::oC_FilterExpression() {
  return getRuleContext<CypherParser::OC_FilterExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ListComprehensionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ListComprehensionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_ListComprehensionContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}


size_t CypherParser::OC_ListComprehensionContext::getRuleIndex() const {
  return CypherParser::RuleOC_ListComprehension;
}

void CypherParser::OC_ListComprehensionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ListComprehension(this);
}

void CypherParser::OC_ListComprehensionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ListComprehension(this);
}


antlrcpp::Any CypherParser::OC_ListComprehensionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ListComprehension(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ListComprehensionContext* CypherParser::oC_ListComprehension() {
  OC_ListComprehensionContext *_localctx = _tracker.createInstance<OC_ListComprehensionContext>(_ctx, getState());
  enterRule(_localctx, 146, CypherParser::RuleOC_ListComprehension);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1253);
    match(CypherParser::T__7);
    setState(1255);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1254);
      match(CypherParser::SP);
    }
    setState(1257);
    oC_FilterExpression();
    setState(1266);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 227, _ctx)) {
    case 1: {
      setState(1259);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1258);
        match(CypherParser::SP);
      }
      setState(1261);
      match(CypherParser::T__10);
      setState(1263);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1262);
        match(CypherParser::SP);
      }
      setState(1265);
      oC_Expression();
      break;
    }

    }
    setState(1269);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1268);
      match(CypherParser::SP);
    }
    setState(1271);
    match(CypherParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PatternComprehensionContext ------------------------------------------------------------------

CypherParser::OC_PatternComprehensionContext::OC_PatternComprehensionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_RelationshipsPatternContext* CypherParser::OC_PatternComprehensionContext::oC_RelationshipsPattern() {
  return getRuleContext<CypherParser::OC_RelationshipsPatternContext>(0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_PatternComprehensionContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_PatternComprehensionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_PatternComprehensionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_VariableContext* CypherParser::OC_PatternComprehensionContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

CypherParser::OC_WhereContext* CypherParser::OC_PatternComprehensionContext::oC_Where() {
  return getRuleContext<CypherParser::OC_WhereContext>(0);
}


size_t CypherParser::OC_PatternComprehensionContext::getRuleIndex() const {
  return CypherParser::RuleOC_PatternComprehension;
}

void CypherParser::OC_PatternComprehensionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PatternComprehension(this);
}

void CypherParser::OC_PatternComprehensionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PatternComprehension(this);
}


antlrcpp::Any CypherParser::OC_PatternComprehensionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PatternComprehension(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PatternComprehensionContext* CypherParser::oC_PatternComprehension() {
  OC_PatternComprehensionContext *_localctx = _tracker.createInstance<OC_PatternComprehensionContext>(_ctx, getState());
  enterRule(_localctx, 148, CypherParser::RuleOC_PatternComprehension);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1273);
    match(CypherParser::T__7);
    setState(1275);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1274);
      match(CypherParser::SP);
    }
    setState(1285);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (CypherParser::COUNT - 83))
      | (1ULL << (CypherParser::ANY - 83))
      | (1ULL << (CypherParser::NONE - 83))
      | (1ULL << (CypherParser::SINGLE - 83))
      | (1ULL << (CypherParser::HexLetter - 83))
      | (1ULL << (CypherParser::FILTER - 83))
      | (1ULL << (CypherParser::EXTRACT - 83))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 83))
      | (1ULL << (CypherParser::EscapedSymbolicName - 83)))) != 0)) {
      setState(1277);
      oC_Variable();
      setState(1279);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1278);
        match(CypherParser::SP);
      }
      setState(1281);
      match(CypherParser::T__2);
      setState(1283);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1282);
        match(CypherParser::SP);
      }
    }
    setState(1287);
    oC_RelationshipsPattern();
    setState(1289);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1288);
      match(CypherParser::SP);
    }
    setState(1295);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::WHERE) {
      setState(1291);
      oC_Where();
      setState(1293);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1292);
        match(CypherParser::SP);
      }
    }
    setState(1297);
    match(CypherParser::T__10);
    setState(1299);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1298);
      match(CypherParser::SP);
    }
    setState(1301);
    oC_Expression();
    setState(1303);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1302);
      match(CypherParser::SP);
    }
    setState(1305);
    match(CypherParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_QuantifierContext ------------------------------------------------------------------

CypherParser::OC_QuantifierContext::OC_QuantifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_QuantifierContext::ALL() {
  return getToken(CypherParser::ALL, 0);
}

CypherParser::OC_FilterExpressionContext* CypherParser::OC_QuantifierContext::oC_FilterExpression() {
  return getRuleContext<CypherParser::OC_FilterExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_QuantifierContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_QuantifierContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_QuantifierContext::ANY() {
  return getToken(CypherParser::ANY, 0);
}

tree::TerminalNode* CypherParser::OC_QuantifierContext::NONE() {
  return getToken(CypherParser::NONE, 0);
}

tree::TerminalNode* CypherParser::OC_QuantifierContext::SINGLE() {
  return getToken(CypherParser::SINGLE, 0);
}


size_t CypherParser::OC_QuantifierContext::getRuleIndex() const {
  return CypherParser::RuleOC_Quantifier;
}

void CypherParser::OC_QuantifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Quantifier(this);
}

void CypherParser::OC_QuantifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Quantifier(this);
}


antlrcpp::Any CypherParser::OC_QuantifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Quantifier(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_QuantifierContext* CypherParser::oC_Quantifier() {
  OC_QuantifierContext *_localctx = _tracker.createInstance<OC_QuantifierContext>(_ctx, getState());
  enterRule(_localctx, 150, CypherParser::RuleOC_Quantifier);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1363);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::ALL: {
        enterOuterAlt(_localctx, 1);
        setState(1307);
        match(CypherParser::ALL);
        setState(1309);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1308);
          match(CypherParser::SP);
        }
        setState(1311);
        match(CypherParser::T__5);
        setState(1313);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1312);
          match(CypherParser::SP);
        }
        setState(1315);
        oC_FilterExpression();
        setState(1317);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1316);
          match(CypherParser::SP);
        }
        setState(1319);
        match(CypherParser::T__6);
        break;
      }

      case CypherParser::ANY: {
        enterOuterAlt(_localctx, 2);
        setState(1321);
        match(CypherParser::ANY);
        setState(1323);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1322);
          match(CypherParser::SP);
        }
        setState(1325);
        match(CypherParser::T__5);
        setState(1327);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1326);
          match(CypherParser::SP);
        }
        setState(1329);
        oC_FilterExpression();
        setState(1331);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1330);
          match(CypherParser::SP);
        }
        setState(1333);
        match(CypherParser::T__6);
        break;
      }

      case CypherParser::NONE: {
        enterOuterAlt(_localctx, 3);
        setState(1335);
        match(CypherParser::NONE);
        setState(1337);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1336);
          match(CypherParser::SP);
        }
        setState(1339);
        match(CypherParser::T__5);
        setState(1341);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1340);
          match(CypherParser::SP);
        }
        setState(1343);
        oC_FilterExpression();
        setState(1345);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1344);
          match(CypherParser::SP);
        }
        setState(1347);
        match(CypherParser::T__6);
        break;
      }

      case CypherParser::SINGLE: {
        enterOuterAlt(_localctx, 4);
        setState(1349);
        match(CypherParser::SINGLE);
        setState(1351);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1350);
          match(CypherParser::SP);
        }
        setState(1353);
        match(CypherParser::T__5);
        setState(1355);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1354);
          match(CypherParser::SP);
        }
        setState(1357);
        oC_FilterExpression();
        setState(1359);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1358);
          match(CypherParser::SP);
        }
        setState(1361);
        match(CypherParser::T__6);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_FilterExpressionContext ------------------------------------------------------------------

CypherParser::OC_FilterExpressionContext::OC_FilterExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_IdInCollContext* CypherParser::OC_FilterExpressionContext::oC_IdInColl() {
  return getRuleContext<CypherParser::OC_IdInCollContext>(0);
}

CypherParser::OC_WhereContext* CypherParser::OC_FilterExpressionContext::oC_Where() {
  return getRuleContext<CypherParser::OC_WhereContext>(0);
}

tree::TerminalNode* CypherParser::OC_FilterExpressionContext::SP() {
  return getToken(CypherParser::SP, 0);
}


size_t CypherParser::OC_FilterExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_FilterExpression;
}

void CypherParser::OC_FilterExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_FilterExpression(this);
}

void CypherParser::OC_FilterExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_FilterExpression(this);
}


antlrcpp::Any CypherParser::OC_FilterExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_FilterExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_FilterExpressionContext* CypherParser::oC_FilterExpression() {
  OC_FilterExpressionContext *_localctx = _tracker.createInstance<OC_FilterExpressionContext>(_ctx, getState());
  enterRule(_localctx, 152, CypherParser::RuleOC_FilterExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1365);
    oC_IdInColl();
    setState(1370);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 252, _ctx)) {
    case 1: {
      setState(1367);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1366);
        match(CypherParser::SP);
      }
      setState(1369);
      oC_Where();
      break;
    }

    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PatternPredicateContext ------------------------------------------------------------------

CypherParser::OC_PatternPredicateContext::OC_PatternPredicateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_RelationshipsPatternContext* CypherParser::OC_PatternPredicateContext::oC_RelationshipsPattern() {
  return getRuleContext<CypherParser::OC_RelationshipsPatternContext>(0);
}


size_t CypherParser::OC_PatternPredicateContext::getRuleIndex() const {
  return CypherParser::RuleOC_PatternPredicate;
}

void CypherParser::OC_PatternPredicateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PatternPredicate(this);
}

void CypherParser::OC_PatternPredicateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PatternPredicate(this);
}


antlrcpp::Any CypherParser::OC_PatternPredicateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PatternPredicate(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PatternPredicateContext* CypherParser::oC_PatternPredicate() {
  OC_PatternPredicateContext *_localctx = _tracker.createInstance<OC_PatternPredicateContext>(_ctx, getState());
  enterRule(_localctx, 154, CypherParser::RuleOC_PatternPredicate);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1372);
    oC_RelationshipsPattern();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ParenthesizedExpressionContext ------------------------------------------------------------------

CypherParser::OC_ParenthesizedExpressionContext::OC_ParenthesizedExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ExpressionContext* CypherParser::OC_ParenthesizedExpressionContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ParenthesizedExpressionContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ParenthesizedExpressionContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}


size_t CypherParser::OC_ParenthesizedExpressionContext::getRuleIndex() const {
  return CypherParser::RuleOC_ParenthesizedExpression;
}

void CypherParser::OC_ParenthesizedExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ParenthesizedExpression(this);
}

void CypherParser::OC_ParenthesizedExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ParenthesizedExpression(this);
}


antlrcpp::Any CypherParser::OC_ParenthesizedExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ParenthesizedExpression(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ParenthesizedExpressionContext* CypherParser::oC_ParenthesizedExpression() {
  OC_ParenthesizedExpressionContext *_localctx = _tracker.createInstance<OC_ParenthesizedExpressionContext>(_ctx, getState());
  enterRule(_localctx, 156, CypherParser::RuleOC_ParenthesizedExpression);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1374);
    match(CypherParser::T__5);
    setState(1376);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1375);
      match(CypherParser::SP);
    }
    setState(1378);
    oC_Expression();
    setState(1380);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1379);
      match(CypherParser::SP);
    }
    setState(1382);
    match(CypherParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_IdInCollContext ------------------------------------------------------------------

CypherParser::OC_IdInCollContext::OC_IdInCollContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_VariableContext* CypherParser::OC_IdInCollContext::oC_Variable() {
  return getRuleContext<CypherParser::OC_VariableContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_IdInCollContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_IdInCollContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_IdInCollContext::IN() {
  return getToken(CypherParser::IN, 0);
}

CypherParser::OC_ExpressionContext* CypherParser::OC_IdInCollContext::oC_Expression() {
  return getRuleContext<CypherParser::OC_ExpressionContext>(0);
}


size_t CypherParser::OC_IdInCollContext::getRuleIndex() const {
  return CypherParser::RuleOC_IdInColl;
}

void CypherParser::OC_IdInCollContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_IdInColl(this);
}

void CypherParser::OC_IdInCollContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_IdInColl(this);
}


antlrcpp::Any CypherParser::OC_IdInCollContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_IdInColl(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_IdInCollContext* CypherParser::oC_IdInColl() {
  OC_IdInCollContext *_localctx = _tracker.createInstance<OC_IdInCollContext>(_ctx, getState());
  enterRule(_localctx, 158, CypherParser::RuleOC_IdInColl);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1384);
    oC_Variable();
    setState(1385);
    match(CypherParser::SP);
    setState(1386);
    match(CypherParser::IN);
    setState(1387);
    match(CypherParser::SP);
    setState(1388);
    oC_Expression();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_FunctionInvocationContext ------------------------------------------------------------------

CypherParser::OC_FunctionInvocationContext::OC_FunctionInvocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_FunctionNameContext* CypherParser::OC_FunctionInvocationContext::oC_FunctionName() {
  return getRuleContext<CypherParser::OC_FunctionNameContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_FunctionInvocationContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_FunctionInvocationContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

tree::TerminalNode* CypherParser::OC_FunctionInvocationContext::DISTINCT() {
  return getToken(CypherParser::DISTINCT, 0);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_FunctionInvocationContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_FunctionInvocationContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}


size_t CypherParser::OC_FunctionInvocationContext::getRuleIndex() const {
  return CypherParser::RuleOC_FunctionInvocation;
}

void CypherParser::OC_FunctionInvocationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_FunctionInvocation(this);
}

void CypherParser::OC_FunctionInvocationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_FunctionInvocation(this);
}


antlrcpp::Any CypherParser::OC_FunctionInvocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_FunctionInvocation(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_FunctionInvocationContext* CypherParser::oC_FunctionInvocation() {
  OC_FunctionInvocationContext *_localctx = _tracker.createInstance<OC_FunctionInvocationContext>(_ctx, getState());
  enterRule(_localctx, 160, CypherParser::RuleOC_FunctionInvocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1390);
    oC_FunctionName();
    setState(1392);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1391);
      match(CypherParser::SP);
    }
    setState(1394);
    match(CypherParser::T__5);
    setState(1396);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1395);
      match(CypherParser::SP);
    }
    setState(1402);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 258, _ctx)) {
    case 1: {
      setState(1398);
      match(CypherParser::DISTINCT);
      setState(1400);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1399);
        match(CypherParser::SP);
      }
      break;
    }

    }
    setState(1421);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::T__5)
      | (1ULL << CypherParser::T__7)
      | (1ULL << CypherParser::T__17)
      | (1ULL << CypherParser::T__18)
      | (1ULL << CypherParser::T__23)
      | (1ULL << CypherParser::T__25)
      | (1ULL << CypherParser::UNION)
      | (1ULL << CypherParser::ALL)
      | (1ULL << CypherParser::OPTIONAL)
      | (1ULL << CypherParser::MATCH)
      | (1ULL << CypherParser::UNWIND)
      | (1ULL << CypherParser::AS)
      | (1ULL << CypherParser::MERGE)
      | (1ULL << CypherParser::ON)
      | (1ULL << CypherParser::CREATE)
      | (1ULL << CypherParser::SET)
      | (1ULL << CypherParser::DETACH)
      | (1ULL << CypherParser::DELETE)
      | (1ULL << CypherParser::REMOVE)
      | (1ULL << CypherParser::WITH)
      | (1ULL << CypherParser::RETURN)
      | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
      | (1ULL << (CypherParser::BY - 64))
      | (1ULL << (CypherParser::L_SKIP - 64))
      | (1ULL << (CypherParser::LIMIT - 64))
      | (1ULL << (CypherParser::ASCENDING - 64))
      | (1ULL << (CypherParser::ASC - 64))
      | (1ULL << (CypherParser::DESCENDING - 64))
      | (1ULL << (CypherParser::DESC - 64))
      | (1ULL << (CypherParser::WHERE - 64))
      | (1ULL << (CypherParser::OR - 64))
      | (1ULL << (CypherParser::XOR - 64))
      | (1ULL << (CypherParser::AND - 64))
      | (1ULL << (CypherParser::NOT - 64))
      | (1ULL << (CypherParser::STARTS - 64))
      | (1ULL << (CypherParser::ENDS - 64))
      | (1ULL << (CypherParser::CONTAINS - 64))
      | (1ULL << (CypherParser::IN - 64))
      | (1ULL << (CypherParser::IS - 64))
      | (1ULL << (CypherParser::CypherNULL - 64))
      | (1ULL << (CypherParser::COUNT - 64))
      | (1ULL << (CypherParser::CASE - 64))
      | (1ULL << (CypherParser::ELSE - 64))
      | (1ULL << (CypherParser::END - 64))
      | (1ULL << (CypherParser::WHEN - 64))
      | (1ULL << (CypherParser::THEN - 64))
      | (1ULL << (CypherParser::ANY - 64))
      | (1ULL << (CypherParser::NONE - 64))
      | (1ULL << (CypherParser::SINGLE - 64))
      | (1ULL << (CypherParser::EXISTS - 64))
      | (1ULL << (CypherParser::TRUE - 64))
      | (1ULL << (CypherParser::FALSE - 64))
      | (1ULL << (CypherParser::HexInteger - 64))
      | (1ULL << (CypherParser::DecimalInteger - 64))
      | (1ULL << (CypherParser::OctalInteger - 64))
      | (1ULL << (CypherParser::HexLetter - 64))
      | (1ULL << (CypherParser::ExponentDecimalReal - 64))
      | (1ULL << (CypherParser::RegularDecimalReal - 64))
      | (1ULL << (CypherParser::StringLiteral - 64))
      | (1ULL << (CypherParser::CONSTRAINT - 64))
      | (1ULL << (CypherParser::DO - 64))
      | (1ULL << (CypherParser::FOR - 64))
      | (1ULL << (CypherParser::REQUIRE - 64))
      | (1ULL << (CypherParser::UNIQUE - 64))
      | (1ULL << (CypherParser::MANDATORY - 64))
      | (1ULL << (CypherParser::SCALAR - 64))
      | (1ULL << (CypherParser::OF - 64))
      | (1ULL << (CypherParser::ADD - 64))
      | (1ULL << (CypherParser::DROP - 64))
      | (1ULL << (CypherParser::FILTER - 64))
      | (1ULL << (CypherParser::EXTRACT - 64))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 64))
      | (1ULL << (CypherParser::EscapedSymbolicName - 64)))) != 0)) {
      setState(1404);
      oC_Expression();
      setState(1406);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1405);
        match(CypherParser::SP);
      }
      setState(1418);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CypherParser::T__1) {
        setState(1408);
        match(CypherParser::T__1);
        setState(1410);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1409);
          match(CypherParser::SP);
        }
        setState(1412);
        oC_Expression();
        setState(1414);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1413);
          match(CypherParser::SP);
        }
        setState(1420);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1423);
    match(CypherParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_FunctionNameContext ------------------------------------------------------------------

CypherParser::OC_FunctionNameContext::OC_FunctionNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_NamespaceContext* CypherParser::OC_FunctionNameContext::oC_Namespace() {
  return getRuleContext<CypherParser::OC_NamespaceContext>(0);
}

CypherParser::OC_SchemaNameContext* CypherParser::OC_FunctionNameContext::oC_SchemaName() {
  return getRuleContext<CypherParser::OC_SchemaNameContext>(0);
}


size_t CypherParser::OC_FunctionNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_FunctionName;
}

void CypherParser::OC_FunctionNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_FunctionName(this);
}

void CypherParser::OC_FunctionNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_FunctionName(this);
}


antlrcpp::Any CypherParser::OC_FunctionNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_FunctionName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_FunctionNameContext* CypherParser::oC_FunctionName() {
  OC_FunctionNameContext *_localctx = _tracker.createInstance<OC_FunctionNameContext>(_ctx, getState());
  enterRule(_localctx, 162, CypherParser::RuleOC_FunctionName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1425);
    oC_Namespace();
    setState(1426);
    oC_SchemaName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ExistentialSubqueryContext ------------------------------------------------------------------

CypherParser::OC_ExistentialSubqueryContext::OC_ExistentialSubqueryContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_ExistentialSubqueryContext::EXISTS() {
  return getToken(CypherParser::EXISTS, 0);
}

CypherParser::OC_RegularQueryContext* CypherParser::OC_ExistentialSubqueryContext::oC_RegularQuery() {
  return getRuleContext<CypherParser::OC_RegularQueryContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ExistentialSubqueryContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ExistentialSubqueryContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

CypherParser::OC_PatternContext* CypherParser::OC_ExistentialSubqueryContext::oC_Pattern() {
  return getRuleContext<CypherParser::OC_PatternContext>(0);
}

CypherParser::OC_WhereContext* CypherParser::OC_ExistentialSubqueryContext::oC_Where() {
  return getRuleContext<CypherParser::OC_WhereContext>(0);
}


size_t CypherParser::OC_ExistentialSubqueryContext::getRuleIndex() const {
  return CypherParser::RuleOC_ExistentialSubquery;
}

void CypherParser::OC_ExistentialSubqueryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ExistentialSubquery(this);
}

void CypherParser::OC_ExistentialSubqueryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ExistentialSubquery(this);
}


antlrcpp::Any CypherParser::OC_ExistentialSubqueryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ExistentialSubquery(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ExistentialSubqueryContext* CypherParser::oC_ExistentialSubquery() {
  OC_ExistentialSubqueryContext *_localctx = _tracker.createInstance<OC_ExistentialSubqueryContext>(_ctx, getState());
  enterRule(_localctx, 164, CypherParser::RuleOC_ExistentialSubquery);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1428);
    match(CypherParser::EXISTS);
    setState(1430);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1429);
      match(CypherParser::SP);
    }
    setState(1432);
    match(CypherParser::T__23);
    setState(1434);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1433);
      match(CypherParser::SP);
    }
    setState(1444);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::OPTIONAL:
      case CypherParser::MATCH:
      case CypherParser::UNWIND:
      case CypherParser::MERGE:
      case CypherParser::CREATE:
      case CypherParser::SET:
      case CypherParser::DETACH:
      case CypherParser::DELETE:
      case CypherParser::REMOVE:
      case CypherParser::CALL:
      case CypherParser::WITH:
      case CypherParser::RETURN: {
        setState(1436);
        oC_RegularQuery();
        break;
      }

      case CypherParser::T__5:
      case CypherParser::COUNT:
      case CypherParser::ANY:
      case CypherParser::NONE:
      case CypherParser::SINGLE:
      case CypherParser::HexLetter:
      case CypherParser::FILTER:
      case CypherParser::EXTRACT:
      case CypherParser::UnescapedSymbolicName:
      case CypherParser::EscapedSymbolicName: {
        setState(1437);
        oC_Pattern();
        setState(1442);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 267, _ctx)) {
        case 1: {
          setState(1439);
          _errHandler->sync(this);

          _la = _input->LA(1);
          if (_la == CypherParser::SP) {
            setState(1438);
            match(CypherParser::SP);
          }
          setState(1441);
          oC_Where();
          break;
        }

        }
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(1447);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1446);
      match(CypherParser::SP);
    }
    setState(1449);
    match(CypherParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ExplicitProcedureInvocationContext ------------------------------------------------------------------

CypherParser::OC_ExplicitProcedureInvocationContext::OC_ExplicitProcedureInvocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ProcedureNameContext* CypherParser::OC_ExplicitProcedureInvocationContext::oC_ProcedureName() {
  return getRuleContext<CypherParser::OC_ProcedureNameContext>(0);
}

std::vector<tree::TerminalNode *> CypherParser::OC_ExplicitProcedureInvocationContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ExplicitProcedureInvocationContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_ExplicitProcedureInvocationContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_ExplicitProcedureInvocationContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}


size_t CypherParser::OC_ExplicitProcedureInvocationContext::getRuleIndex() const {
  return CypherParser::RuleOC_ExplicitProcedureInvocation;
}

void CypherParser::OC_ExplicitProcedureInvocationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ExplicitProcedureInvocation(this);
}

void CypherParser::OC_ExplicitProcedureInvocationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ExplicitProcedureInvocation(this);
}


antlrcpp::Any CypherParser::OC_ExplicitProcedureInvocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ExplicitProcedureInvocation(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ExplicitProcedureInvocationContext* CypherParser::oC_ExplicitProcedureInvocation() {
  OC_ExplicitProcedureInvocationContext *_localctx = _tracker.createInstance<OC_ExplicitProcedureInvocationContext>(_ctx, getState());
  enterRule(_localctx, 166, CypherParser::RuleOC_ExplicitProcedureInvocation);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1451);
    oC_ProcedureName();
    setState(1453);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1452);
      match(CypherParser::SP);
    }
    setState(1455);
    match(CypherParser::T__5);
    setState(1457);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1456);
      match(CypherParser::SP);
    }
    setState(1476);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::T__5)
      | (1ULL << CypherParser::T__7)
      | (1ULL << CypherParser::T__17)
      | (1ULL << CypherParser::T__18)
      | (1ULL << CypherParser::T__23)
      | (1ULL << CypherParser::T__25)
      | (1ULL << CypherParser::UNION)
      | (1ULL << CypherParser::ALL)
      | (1ULL << CypherParser::OPTIONAL)
      | (1ULL << CypherParser::MATCH)
      | (1ULL << CypherParser::UNWIND)
      | (1ULL << CypherParser::AS)
      | (1ULL << CypherParser::MERGE)
      | (1ULL << CypherParser::ON)
      | (1ULL << CypherParser::CREATE)
      | (1ULL << CypherParser::SET)
      | (1ULL << CypherParser::DETACH)
      | (1ULL << CypherParser::DELETE)
      | (1ULL << CypherParser::REMOVE)
      | (1ULL << CypherParser::WITH)
      | (1ULL << CypherParser::RETURN)
      | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
      | (1ULL << (CypherParser::BY - 64))
      | (1ULL << (CypherParser::L_SKIP - 64))
      | (1ULL << (CypherParser::LIMIT - 64))
      | (1ULL << (CypherParser::ASCENDING - 64))
      | (1ULL << (CypherParser::ASC - 64))
      | (1ULL << (CypherParser::DESCENDING - 64))
      | (1ULL << (CypherParser::DESC - 64))
      | (1ULL << (CypherParser::WHERE - 64))
      | (1ULL << (CypherParser::OR - 64))
      | (1ULL << (CypherParser::XOR - 64))
      | (1ULL << (CypherParser::AND - 64))
      | (1ULL << (CypherParser::NOT - 64))
      | (1ULL << (CypherParser::STARTS - 64))
      | (1ULL << (CypherParser::ENDS - 64))
      | (1ULL << (CypherParser::CONTAINS - 64))
      | (1ULL << (CypherParser::IN - 64))
      | (1ULL << (CypherParser::IS - 64))
      | (1ULL << (CypherParser::CypherNULL - 64))
      | (1ULL << (CypherParser::COUNT - 64))
      | (1ULL << (CypherParser::CASE - 64))
      | (1ULL << (CypherParser::ELSE - 64))
      | (1ULL << (CypherParser::END - 64))
      | (1ULL << (CypherParser::WHEN - 64))
      | (1ULL << (CypherParser::THEN - 64))
      | (1ULL << (CypherParser::ANY - 64))
      | (1ULL << (CypherParser::NONE - 64))
      | (1ULL << (CypherParser::SINGLE - 64))
      | (1ULL << (CypherParser::EXISTS - 64))
      | (1ULL << (CypherParser::TRUE - 64))
      | (1ULL << (CypherParser::FALSE - 64))
      | (1ULL << (CypherParser::HexInteger - 64))
      | (1ULL << (CypherParser::DecimalInteger - 64))
      | (1ULL << (CypherParser::OctalInteger - 64))
      | (1ULL << (CypherParser::HexLetter - 64))
      | (1ULL << (CypherParser::ExponentDecimalReal - 64))
      | (1ULL << (CypherParser::RegularDecimalReal - 64))
      | (1ULL << (CypherParser::StringLiteral - 64))
      | (1ULL << (CypherParser::CONSTRAINT - 64))
      | (1ULL << (CypherParser::DO - 64))
      | (1ULL << (CypherParser::FOR - 64))
      | (1ULL << (CypherParser::REQUIRE - 64))
      | (1ULL << (CypherParser::UNIQUE - 64))
      | (1ULL << (CypherParser::MANDATORY - 64))
      | (1ULL << (CypherParser::SCALAR - 64))
      | (1ULL << (CypherParser::OF - 64))
      | (1ULL << (CypherParser::ADD - 64))
      | (1ULL << (CypherParser::DROP - 64))
      | (1ULL << (CypherParser::FILTER - 64))
      | (1ULL << (CypherParser::EXTRACT - 64))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 64))
      | (1ULL << (CypherParser::EscapedSymbolicName - 64)))) != 0)) {
      setState(1459);
      oC_Expression();
      setState(1461);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1460);
        match(CypherParser::SP);
      }
      setState(1473);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CypherParser::T__1) {
        setState(1463);
        match(CypherParser::T__1);
        setState(1465);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1464);
          match(CypherParser::SP);
        }
        setState(1467);
        oC_Expression();
        setState(1469);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1468);
          match(CypherParser::SP);
        }
        setState(1475);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1478);
    match(CypherParser::T__6);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ImplicitProcedureInvocationContext ------------------------------------------------------------------

CypherParser::OC_ImplicitProcedureInvocationContext::OC_ImplicitProcedureInvocationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_ProcedureNameContext* CypherParser::OC_ImplicitProcedureInvocationContext::oC_ProcedureName() {
  return getRuleContext<CypherParser::OC_ProcedureNameContext>(0);
}


size_t CypherParser::OC_ImplicitProcedureInvocationContext::getRuleIndex() const {
  return CypherParser::RuleOC_ImplicitProcedureInvocation;
}

void CypherParser::OC_ImplicitProcedureInvocationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ImplicitProcedureInvocation(this);
}

void CypherParser::OC_ImplicitProcedureInvocationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ImplicitProcedureInvocation(this);
}


antlrcpp::Any CypherParser::OC_ImplicitProcedureInvocationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ImplicitProcedureInvocation(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ImplicitProcedureInvocationContext* CypherParser::oC_ImplicitProcedureInvocation() {
  OC_ImplicitProcedureInvocationContext *_localctx = _tracker.createInstance<OC_ImplicitProcedureInvocationContext>(_ctx, getState());
  enterRule(_localctx, 168, CypherParser::RuleOC_ImplicitProcedureInvocation);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1480);
    oC_ProcedureName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ProcedureResultFieldContext ------------------------------------------------------------------

CypherParser::OC_ProcedureResultFieldContext::OC_ProcedureResultFieldContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SymbolicNameContext* CypherParser::OC_ProcedureResultFieldContext::oC_SymbolicName() {
  return getRuleContext<CypherParser::OC_SymbolicNameContext>(0);
}


size_t CypherParser::OC_ProcedureResultFieldContext::getRuleIndex() const {
  return CypherParser::RuleOC_ProcedureResultField;
}

void CypherParser::OC_ProcedureResultFieldContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ProcedureResultField(this);
}

void CypherParser::OC_ProcedureResultFieldContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ProcedureResultField(this);
}


antlrcpp::Any CypherParser::OC_ProcedureResultFieldContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ProcedureResultField(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ProcedureResultFieldContext* CypherParser::oC_ProcedureResultField() {
  OC_ProcedureResultFieldContext *_localctx = _tracker.createInstance<OC_ProcedureResultFieldContext>(_ctx, getState());
  enterRule(_localctx, 170, CypherParser::RuleOC_ProcedureResultField);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1482);
    oC_SymbolicName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ProcedureNameContext ------------------------------------------------------------------

CypherParser::OC_ProcedureNameContext::OC_ProcedureNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_NamespaceContext* CypherParser::OC_ProcedureNameContext::oC_Namespace() {
  return getRuleContext<CypherParser::OC_NamespaceContext>(0);
}

CypherParser::OC_SchemaNameContext* CypherParser::OC_ProcedureNameContext::oC_SchemaName() {
  return getRuleContext<CypherParser::OC_SchemaNameContext>(0);
}


size_t CypherParser::OC_ProcedureNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_ProcedureName;
}

void CypherParser::OC_ProcedureNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ProcedureName(this);
}

void CypherParser::OC_ProcedureNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ProcedureName(this);
}


antlrcpp::Any CypherParser::OC_ProcedureNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ProcedureName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ProcedureNameContext* CypherParser::oC_ProcedureName() {
  OC_ProcedureNameContext *_localctx = _tracker.createInstance<OC_ProcedureNameContext>(_ctx, getState());
  enterRule(_localctx, 172, CypherParser::RuleOC_ProcedureName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1484);
    oC_Namespace();
    setState(1485);
    oC_SchemaName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NamespaceContext ------------------------------------------------------------------

CypherParser::OC_NamespaceContext::OC_NamespaceContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CypherParser::OC_SchemaNameContext *> CypherParser::OC_NamespaceContext::oC_SchemaName() {
  return getRuleContexts<CypherParser::OC_SchemaNameContext>();
}

CypherParser::OC_SchemaNameContext* CypherParser::OC_NamespaceContext::oC_SchemaName(size_t i) {
  return getRuleContext<CypherParser::OC_SchemaNameContext>(i);
}


size_t CypherParser::OC_NamespaceContext::getRuleIndex() const {
  return CypherParser::RuleOC_Namespace;
}

void CypherParser::OC_NamespaceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Namespace(this);
}

void CypherParser::OC_NamespaceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Namespace(this);
}


antlrcpp::Any CypherParser::OC_NamespaceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Namespace(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NamespaceContext* CypherParser::oC_Namespace() {
  OC_NamespaceContext *_localctx = _tracker.createInstance<OC_NamespaceContext>(_ctx, getState());
  enterRule(_localctx, 174, CypherParser::RuleOC_Namespace);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(1492);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 277, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        setState(1487);
        oC_SchemaName();
        setState(1488);
        match(CypherParser::T__22); 
      }
      setState(1494);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 277, _ctx);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_VariableContext ------------------------------------------------------------------

CypherParser::OC_VariableContext::OC_VariableContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SymbolicNameContext* CypherParser::OC_VariableContext::oC_SymbolicName() {
  return getRuleContext<CypherParser::OC_SymbolicNameContext>(0);
}


size_t CypherParser::OC_VariableContext::getRuleIndex() const {
  return CypherParser::RuleOC_Variable;
}

void CypherParser::OC_VariableContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Variable(this);
}

void CypherParser::OC_VariableContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Variable(this);
}


antlrcpp::Any CypherParser::OC_VariableContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Variable(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_VariableContext* CypherParser::oC_Variable() {
  OC_VariableContext *_localctx = _tracker.createInstance<OC_VariableContext>(_ctx, getState());
  enterRule(_localctx, 176, CypherParser::RuleOC_Variable);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1495);
    oC_SymbolicName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_LiteralContext ------------------------------------------------------------------

CypherParser::OC_LiteralContext::OC_LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_BooleanLiteralContext* CypherParser::OC_LiteralContext::oC_BooleanLiteral() {
  return getRuleContext<CypherParser::OC_BooleanLiteralContext>(0);
}

tree::TerminalNode* CypherParser::OC_LiteralContext::CypherNULL() {
  return getToken(CypherParser::CypherNULL, 0);
}

CypherParser::OC_NumberLiteralContext* CypherParser::OC_LiteralContext::oC_NumberLiteral() {
  return getRuleContext<CypherParser::OC_NumberLiteralContext>(0);
}

tree::TerminalNode* CypherParser::OC_LiteralContext::StringLiteral() {
  return getToken(CypherParser::StringLiteral, 0);
}

CypherParser::OC_ListLiteralContext* CypherParser::OC_LiteralContext::oC_ListLiteral() {
  return getRuleContext<CypherParser::OC_ListLiteralContext>(0);
}

CypherParser::OC_MapLiteralContext* CypherParser::OC_LiteralContext::oC_MapLiteral() {
  return getRuleContext<CypherParser::OC_MapLiteralContext>(0);
}


size_t CypherParser::OC_LiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_Literal;
}

void CypherParser::OC_LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Literal(this);
}

void CypherParser::OC_LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Literal(this);
}


antlrcpp::Any CypherParser::OC_LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Literal(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_LiteralContext* CypherParser::oC_Literal() {
  OC_LiteralContext *_localctx = _tracker.createInstance<OC_LiteralContext>(_ctx, getState());
  enterRule(_localctx, 178, CypherParser::RuleOC_Literal);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1503);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::TRUE:
      case CypherParser::FALSE: {
        enterOuterAlt(_localctx, 1);
        setState(1497);
        oC_BooleanLiteral();
        break;
      }

      case CypherParser::CypherNULL: {
        enterOuterAlt(_localctx, 2);
        setState(1498);
        match(CypherParser::CypherNULL);
        break;
      }

      case CypherParser::HexInteger:
      case CypherParser::DecimalInteger:
      case CypherParser::OctalInteger:
      case CypherParser::ExponentDecimalReal:
      case CypherParser::RegularDecimalReal: {
        enterOuterAlt(_localctx, 3);
        setState(1499);
        oC_NumberLiteral();
        break;
      }

      case CypherParser::StringLiteral: {
        enterOuterAlt(_localctx, 4);
        setState(1500);
        match(CypherParser::StringLiteral);
        break;
      }

      case CypherParser::T__7: {
        enterOuterAlt(_localctx, 5);
        setState(1501);
        oC_ListLiteral();
        break;
      }

      case CypherParser::T__23: {
        enterOuterAlt(_localctx, 6);
        setState(1502);
        oC_MapLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_BooleanLiteralContext ------------------------------------------------------------------

CypherParser::OC_BooleanLiteralContext::OC_BooleanLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_BooleanLiteralContext::TRUE() {
  return getToken(CypherParser::TRUE, 0);
}

tree::TerminalNode* CypherParser::OC_BooleanLiteralContext::FALSE() {
  return getToken(CypherParser::FALSE, 0);
}


size_t CypherParser::OC_BooleanLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_BooleanLiteral;
}

void CypherParser::OC_BooleanLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_BooleanLiteral(this);
}

void CypherParser::OC_BooleanLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_BooleanLiteral(this);
}


antlrcpp::Any CypherParser::OC_BooleanLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_BooleanLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_BooleanLiteralContext* CypherParser::oC_BooleanLiteral() {
  OC_BooleanLiteralContext *_localctx = _tracker.createInstance<OC_BooleanLiteralContext>(_ctx, getState());
  enterRule(_localctx, 180, CypherParser::RuleOC_BooleanLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1505);
    _la = _input->LA(1);
    if (!(_la == CypherParser::TRUE

    || _la == CypherParser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_NumberLiteralContext ------------------------------------------------------------------

CypherParser::OC_NumberLiteralContext::OC_NumberLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_DoubleLiteralContext* CypherParser::OC_NumberLiteralContext::oC_DoubleLiteral() {
  return getRuleContext<CypherParser::OC_DoubleLiteralContext>(0);
}

CypherParser::OC_IntegerLiteralContext* CypherParser::OC_NumberLiteralContext::oC_IntegerLiteral() {
  return getRuleContext<CypherParser::OC_IntegerLiteralContext>(0);
}


size_t CypherParser::OC_NumberLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_NumberLiteral;
}

void CypherParser::OC_NumberLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_NumberLiteral(this);
}

void CypherParser::OC_NumberLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_NumberLiteral(this);
}


antlrcpp::Any CypherParser::OC_NumberLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_NumberLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_NumberLiteralContext* CypherParser::oC_NumberLiteral() {
  OC_NumberLiteralContext *_localctx = _tracker.createInstance<OC_NumberLiteralContext>(_ctx, getState());
  enterRule(_localctx, 182, CypherParser::RuleOC_NumberLiteral);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1509);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::ExponentDecimalReal:
      case CypherParser::RegularDecimalReal: {
        enterOuterAlt(_localctx, 1);
        setState(1507);
        oC_DoubleLiteral();
        break;
      }

      case CypherParser::HexInteger:
      case CypherParser::DecimalInteger:
      case CypherParser::OctalInteger: {
        enterOuterAlt(_localctx, 2);
        setState(1508);
        oC_IntegerLiteral();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_IntegerLiteralContext ------------------------------------------------------------------

CypherParser::OC_IntegerLiteralContext::OC_IntegerLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_IntegerLiteralContext::HexInteger() {
  return getToken(CypherParser::HexInteger, 0);
}

tree::TerminalNode* CypherParser::OC_IntegerLiteralContext::OctalInteger() {
  return getToken(CypherParser::OctalInteger, 0);
}

tree::TerminalNode* CypherParser::OC_IntegerLiteralContext::DecimalInteger() {
  return getToken(CypherParser::DecimalInteger, 0);
}


size_t CypherParser::OC_IntegerLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_IntegerLiteral;
}

void CypherParser::OC_IntegerLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_IntegerLiteral(this);
}

void CypherParser::OC_IntegerLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_IntegerLiteral(this);
}


antlrcpp::Any CypherParser::OC_IntegerLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_IntegerLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_IntegerLiteralContext* CypherParser::oC_IntegerLiteral() {
  OC_IntegerLiteralContext *_localctx = _tracker.createInstance<OC_IntegerLiteralContext>(_ctx, getState());
  enterRule(_localctx, 184, CypherParser::RuleOC_IntegerLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1511);
    _la = _input->LA(1);
    if (!(((((_la - 95) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 95)) & ((1ULL << (CypherParser::HexInteger - 95))
      | (1ULL << (CypherParser::DecimalInteger - 95))
      | (1ULL << (CypherParser::OctalInteger - 95)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_DoubleLiteralContext ------------------------------------------------------------------

CypherParser::OC_DoubleLiteralContext::OC_DoubleLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_DoubleLiteralContext::ExponentDecimalReal() {
  return getToken(CypherParser::ExponentDecimalReal, 0);
}

tree::TerminalNode* CypherParser::OC_DoubleLiteralContext::RegularDecimalReal() {
  return getToken(CypherParser::RegularDecimalReal, 0);
}


size_t CypherParser::OC_DoubleLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_DoubleLiteral;
}

void CypherParser::OC_DoubleLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_DoubleLiteral(this);
}

void CypherParser::OC_DoubleLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_DoubleLiteral(this);
}


antlrcpp::Any CypherParser::OC_DoubleLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_DoubleLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_DoubleLiteralContext* CypherParser::oC_DoubleLiteral() {
  OC_DoubleLiteralContext *_localctx = _tracker.createInstance<OC_DoubleLiteralContext>(_ctx, getState());
  enterRule(_localctx, 186, CypherParser::RuleOC_DoubleLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1513);
    _la = _input->LA(1);
    if (!(_la == CypherParser::ExponentDecimalReal

    || _la == CypherParser::RegularDecimalReal)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ListLiteralContext ------------------------------------------------------------------

CypherParser::OC_ListLiteralContext::OC_ListLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_ListLiteralContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_ListLiteralContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_ListLiteralContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_ListLiteralContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}


size_t CypherParser::OC_ListLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_ListLiteral;
}

void CypherParser::OC_ListLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ListLiteral(this);
}

void CypherParser::OC_ListLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ListLiteral(this);
}


antlrcpp::Any CypherParser::OC_ListLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ListLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ListLiteralContext* CypherParser::oC_ListLiteral() {
  OC_ListLiteralContext *_localctx = _tracker.createInstance<OC_ListLiteralContext>(_ctx, getState());
  enterRule(_localctx, 188, CypherParser::RuleOC_ListLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1515);
    match(CypherParser::T__7);
    setState(1517);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1516);
      match(CypherParser::SP);
    }
    setState(1536);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::T__5)
      | (1ULL << CypherParser::T__7)
      | (1ULL << CypherParser::T__17)
      | (1ULL << CypherParser::T__18)
      | (1ULL << CypherParser::T__23)
      | (1ULL << CypherParser::T__25)
      | (1ULL << CypherParser::UNION)
      | (1ULL << CypherParser::ALL)
      | (1ULL << CypherParser::OPTIONAL)
      | (1ULL << CypherParser::MATCH)
      | (1ULL << CypherParser::UNWIND)
      | (1ULL << CypherParser::AS)
      | (1ULL << CypherParser::MERGE)
      | (1ULL << CypherParser::ON)
      | (1ULL << CypherParser::CREATE)
      | (1ULL << CypherParser::SET)
      | (1ULL << CypherParser::DETACH)
      | (1ULL << CypherParser::DELETE)
      | (1ULL << CypherParser::REMOVE)
      | (1ULL << CypherParser::WITH)
      | (1ULL << CypherParser::RETURN)
      | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
      | (1ULL << (CypherParser::BY - 64))
      | (1ULL << (CypherParser::L_SKIP - 64))
      | (1ULL << (CypherParser::LIMIT - 64))
      | (1ULL << (CypherParser::ASCENDING - 64))
      | (1ULL << (CypherParser::ASC - 64))
      | (1ULL << (CypherParser::DESCENDING - 64))
      | (1ULL << (CypherParser::DESC - 64))
      | (1ULL << (CypherParser::WHERE - 64))
      | (1ULL << (CypherParser::OR - 64))
      | (1ULL << (CypherParser::XOR - 64))
      | (1ULL << (CypherParser::AND - 64))
      | (1ULL << (CypherParser::NOT - 64))
      | (1ULL << (CypherParser::STARTS - 64))
      | (1ULL << (CypherParser::ENDS - 64))
      | (1ULL << (CypherParser::CONTAINS - 64))
      | (1ULL << (CypherParser::IN - 64))
      | (1ULL << (CypherParser::IS - 64))
      | (1ULL << (CypherParser::CypherNULL - 64))
      | (1ULL << (CypherParser::COUNT - 64))
      | (1ULL << (CypherParser::CASE - 64))
      | (1ULL << (CypherParser::ELSE - 64))
      | (1ULL << (CypherParser::END - 64))
      | (1ULL << (CypherParser::WHEN - 64))
      | (1ULL << (CypherParser::THEN - 64))
      | (1ULL << (CypherParser::ANY - 64))
      | (1ULL << (CypherParser::NONE - 64))
      | (1ULL << (CypherParser::SINGLE - 64))
      | (1ULL << (CypherParser::EXISTS - 64))
      | (1ULL << (CypherParser::TRUE - 64))
      | (1ULL << (CypherParser::FALSE - 64))
      | (1ULL << (CypherParser::HexInteger - 64))
      | (1ULL << (CypherParser::DecimalInteger - 64))
      | (1ULL << (CypherParser::OctalInteger - 64))
      | (1ULL << (CypherParser::HexLetter - 64))
      | (1ULL << (CypherParser::ExponentDecimalReal - 64))
      | (1ULL << (CypherParser::RegularDecimalReal - 64))
      | (1ULL << (CypherParser::StringLiteral - 64))
      | (1ULL << (CypherParser::CONSTRAINT - 64))
      | (1ULL << (CypherParser::DO - 64))
      | (1ULL << (CypherParser::FOR - 64))
      | (1ULL << (CypherParser::REQUIRE - 64))
      | (1ULL << (CypherParser::UNIQUE - 64))
      | (1ULL << (CypherParser::MANDATORY - 64))
      | (1ULL << (CypherParser::SCALAR - 64))
      | (1ULL << (CypherParser::OF - 64))
      | (1ULL << (CypherParser::ADD - 64))
      | (1ULL << (CypherParser::DROP - 64))
      | (1ULL << (CypherParser::FILTER - 64))
      | (1ULL << (CypherParser::EXTRACT - 64))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 64))
      | (1ULL << (CypherParser::EscapedSymbolicName - 64)))) != 0)) {
      setState(1519);
      oC_Expression();
      setState(1521);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1520);
        match(CypherParser::SP);
      }
      setState(1533);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CypherParser::T__1) {
        setState(1523);
        match(CypherParser::T__1);
        setState(1525);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1524);
          match(CypherParser::SP);
        }
        setState(1527);
        oC_Expression();
        setState(1529);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1528);
          match(CypherParser::SP);
        }
        setState(1535);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1538);
    match(CypherParser::T__8);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_MapLiteralContext ------------------------------------------------------------------

CypherParser::OC_MapLiteralContext::OC_MapLiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<tree::TerminalNode *> CypherParser::OC_MapLiteralContext::SP() {
  return getTokens(CypherParser::SP);
}

tree::TerminalNode* CypherParser::OC_MapLiteralContext::SP(size_t i) {
  return getToken(CypherParser::SP, i);
}

std::vector<CypherParser::OC_PropertyKeyNameContext *> CypherParser::OC_MapLiteralContext::oC_PropertyKeyName() {
  return getRuleContexts<CypherParser::OC_PropertyKeyNameContext>();
}

CypherParser::OC_PropertyKeyNameContext* CypherParser::OC_MapLiteralContext::oC_PropertyKeyName(size_t i) {
  return getRuleContext<CypherParser::OC_PropertyKeyNameContext>(i);
}

std::vector<CypherParser::OC_ExpressionContext *> CypherParser::OC_MapLiteralContext::oC_Expression() {
  return getRuleContexts<CypherParser::OC_ExpressionContext>();
}

CypherParser::OC_ExpressionContext* CypherParser::OC_MapLiteralContext::oC_Expression(size_t i) {
  return getRuleContext<CypherParser::OC_ExpressionContext>(i);
}


size_t CypherParser::OC_MapLiteralContext::getRuleIndex() const {
  return CypherParser::RuleOC_MapLiteral;
}

void CypherParser::OC_MapLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_MapLiteral(this);
}

void CypherParser::OC_MapLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_MapLiteral(this);
}


antlrcpp::Any CypherParser::OC_MapLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_MapLiteral(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_MapLiteralContext* CypherParser::oC_MapLiteral() {
  OC_MapLiteralContext *_localctx = _tracker.createInstance<OC_MapLiteralContext>(_ctx, getState());
  enterRule(_localctx, 190, CypherParser::RuleOC_MapLiteral);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1540);
    match(CypherParser::T__23);
    setState(1542);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CypherParser::SP) {
      setState(1541);
      match(CypherParser::SP);
    }
    setState(1577);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::UNION)
      | (1ULL << CypherParser::ALL)
      | (1ULL << CypherParser::OPTIONAL)
      | (1ULL << CypherParser::MATCH)
      | (1ULL << CypherParser::UNWIND)
      | (1ULL << CypherParser::AS)
      | (1ULL << CypherParser::MERGE)
      | (1ULL << CypherParser::ON)
      | (1ULL << CypherParser::CREATE)
      | (1ULL << CypherParser::SET)
      | (1ULL << CypherParser::DETACH)
      | (1ULL << CypherParser::DELETE)
      | (1ULL << CypherParser::REMOVE)
      | (1ULL << CypherParser::WITH)
      | (1ULL << CypherParser::RETURN)
      | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
      | (1ULL << (CypherParser::BY - 64))
      | (1ULL << (CypherParser::L_SKIP - 64))
      | (1ULL << (CypherParser::LIMIT - 64))
      | (1ULL << (CypherParser::ASCENDING - 64))
      | (1ULL << (CypherParser::ASC - 64))
      | (1ULL << (CypherParser::DESCENDING - 64))
      | (1ULL << (CypherParser::DESC - 64))
      | (1ULL << (CypherParser::WHERE - 64))
      | (1ULL << (CypherParser::OR - 64))
      | (1ULL << (CypherParser::XOR - 64))
      | (1ULL << (CypherParser::AND - 64))
      | (1ULL << (CypherParser::NOT - 64))
      | (1ULL << (CypherParser::STARTS - 64))
      | (1ULL << (CypherParser::ENDS - 64))
      | (1ULL << (CypherParser::CONTAINS - 64))
      | (1ULL << (CypherParser::IN - 64))
      | (1ULL << (CypherParser::IS - 64))
      | (1ULL << (CypherParser::CypherNULL - 64))
      | (1ULL << (CypherParser::COUNT - 64))
      | (1ULL << (CypherParser::CASE - 64))
      | (1ULL << (CypherParser::ELSE - 64))
      | (1ULL << (CypherParser::END - 64))
      | (1ULL << (CypherParser::WHEN - 64))
      | (1ULL << (CypherParser::THEN - 64))
      | (1ULL << (CypherParser::ANY - 64))
      | (1ULL << (CypherParser::NONE - 64))
      | (1ULL << (CypherParser::SINGLE - 64))
      | (1ULL << (CypherParser::EXISTS - 64))
      | (1ULL << (CypherParser::TRUE - 64))
      | (1ULL << (CypherParser::FALSE - 64))
      | (1ULL << (CypherParser::HexLetter - 64))
      | (1ULL << (CypherParser::CONSTRAINT - 64))
      | (1ULL << (CypherParser::DO - 64))
      | (1ULL << (CypherParser::FOR - 64))
      | (1ULL << (CypherParser::REQUIRE - 64))
      | (1ULL << (CypherParser::UNIQUE - 64))
      | (1ULL << (CypherParser::MANDATORY - 64))
      | (1ULL << (CypherParser::SCALAR - 64))
      | (1ULL << (CypherParser::OF - 64))
      | (1ULL << (CypherParser::ADD - 64))
      | (1ULL << (CypherParser::DROP - 64))
      | (1ULL << (CypherParser::FILTER - 64))
      | (1ULL << (CypherParser::EXTRACT - 64))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 64))
      | (1ULL << (CypherParser::EscapedSymbolicName - 64)))) != 0)) {
      setState(1544);
      oC_PropertyKeyName();
      setState(1546);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1545);
        match(CypherParser::SP);
      }
      setState(1548);
      match(CypherParser::T__9);
      setState(1550);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1549);
        match(CypherParser::SP);
      }
      setState(1552);
      oC_Expression();
      setState(1554);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if (_la == CypherParser::SP) {
        setState(1553);
        match(CypherParser::SP);
      }
      setState(1574);
      _errHandler->sync(this);
      _la = _input->LA(1);
      while (_la == CypherParser::T__1) {
        setState(1556);
        match(CypherParser::T__1);
        setState(1558);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1557);
          match(CypherParser::SP);
        }
        setState(1560);
        oC_PropertyKeyName();
        setState(1562);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1561);
          match(CypherParser::SP);
        }
        setState(1564);
        match(CypherParser::T__9);
        setState(1566);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1565);
          match(CypherParser::SP);
        }
        setState(1568);
        oC_Expression();
        setState(1570);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CypherParser::SP) {
          setState(1569);
          match(CypherParser::SP);
        }
        setState(1576);
        _errHandler->sync(this);
        _la = _input->LA(1);
      }
    }
    setState(1579);
    match(CypherParser::T__24);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_PropertyKeyNameContext ------------------------------------------------------------------

CypherParser::OC_PropertyKeyNameContext::OC_PropertyKeyNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SchemaNameContext* CypherParser::OC_PropertyKeyNameContext::oC_SchemaName() {
  return getRuleContext<CypherParser::OC_SchemaNameContext>(0);
}


size_t CypherParser::OC_PropertyKeyNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_PropertyKeyName;
}

void CypherParser::OC_PropertyKeyNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_PropertyKeyName(this);
}

void CypherParser::OC_PropertyKeyNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_PropertyKeyName(this);
}


antlrcpp::Any CypherParser::OC_PropertyKeyNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_PropertyKeyName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_PropertyKeyNameContext* CypherParser::oC_PropertyKeyName() {
  OC_PropertyKeyNameContext *_localctx = _tracker.createInstance<OC_PropertyKeyNameContext>(_ctx, getState());
  enterRule(_localctx, 192, CypherParser::RuleOC_PropertyKeyName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1581);
    oC_SchemaName();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ParameterContext ------------------------------------------------------------------

CypherParser::OC_ParameterContext::OC_ParameterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SymbolicNameContext* CypherParser::OC_ParameterContext::oC_SymbolicName() {
  return getRuleContext<CypherParser::OC_SymbolicNameContext>(0);
}

tree::TerminalNode* CypherParser::OC_ParameterContext::DecimalInteger() {
  return getToken(CypherParser::DecimalInteger, 0);
}


size_t CypherParser::OC_ParameterContext::getRuleIndex() const {
  return CypherParser::RuleOC_Parameter;
}

void CypherParser::OC_ParameterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Parameter(this);
}

void CypherParser::OC_ParameterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Parameter(this);
}


antlrcpp::Any CypherParser::OC_ParameterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Parameter(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ParameterContext* CypherParser::oC_Parameter() {
  OC_ParameterContext *_localctx = _tracker.createInstance<OC_ParameterContext>(_ctx, getState());
  enterRule(_localctx, 194, CypherParser::RuleOC_Parameter);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1583);
    match(CypherParser::T__25);
    setState(1586);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::COUNT:
      case CypherParser::ANY:
      case CypherParser::NONE:
      case CypherParser::SINGLE:
      case CypherParser::HexLetter:
      case CypherParser::FILTER:
      case CypherParser::EXTRACT:
      case CypherParser::UnescapedSymbolicName:
      case CypherParser::EscapedSymbolicName: {
        setState(1584);
        oC_SymbolicName();
        break;
      }

      case CypherParser::DecimalInteger: {
        setState(1585);
        match(CypherParser::DecimalInteger);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SchemaNameContext ------------------------------------------------------------------

CypherParser::OC_SchemaNameContext::OC_SchemaNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CypherParser::OC_SymbolicNameContext* CypherParser::OC_SchemaNameContext::oC_SymbolicName() {
  return getRuleContext<CypherParser::OC_SymbolicNameContext>(0);
}

CypherParser::OC_ReservedWordContext* CypherParser::OC_SchemaNameContext::oC_ReservedWord() {
  return getRuleContext<CypherParser::OC_ReservedWordContext>(0);
}


size_t CypherParser::OC_SchemaNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_SchemaName;
}

void CypherParser::OC_SchemaNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_SchemaName(this);
}

void CypherParser::OC_SchemaNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_SchemaName(this);
}


antlrcpp::Any CypherParser::OC_SchemaNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_SchemaName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SchemaNameContext* CypherParser::oC_SchemaName() {
  OC_SchemaNameContext *_localctx = _tracker.createInstance<OC_SchemaNameContext>(_ctx, getState());
  enterRule(_localctx, 196, CypherParser::RuleOC_SchemaName);

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    setState(1590);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CypherParser::COUNT:
      case CypherParser::ANY:
      case CypherParser::NONE:
      case CypherParser::SINGLE:
      case CypherParser::HexLetter:
      case CypherParser::FILTER:
      case CypherParser::EXTRACT:
      case CypherParser::UnescapedSymbolicName:
      case CypherParser::EscapedSymbolicName: {
        enterOuterAlt(_localctx, 1);
        setState(1588);
        oC_SymbolicName();
        break;
      }

      case CypherParser::UNION:
      case CypherParser::ALL:
      case CypherParser::OPTIONAL:
      case CypherParser::MATCH:
      case CypherParser::UNWIND:
      case CypherParser::AS:
      case CypherParser::MERGE:
      case CypherParser::ON:
      case CypherParser::CREATE:
      case CypherParser::SET:
      case CypherParser::DETACH:
      case CypherParser::DELETE:
      case CypherParser::REMOVE:
      case CypherParser::WITH:
      case CypherParser::RETURN:
      case CypherParser::DISTINCT:
      case CypherParser::ORDER:
      case CypherParser::BY:
      case CypherParser::L_SKIP:
      case CypherParser::LIMIT:
      case CypherParser::ASCENDING:
      case CypherParser::ASC:
      case CypherParser::DESCENDING:
      case CypherParser::DESC:
      case CypherParser::WHERE:
      case CypherParser::OR:
      case CypherParser::XOR:
      case CypherParser::AND:
      case CypherParser::NOT:
      case CypherParser::STARTS:
      case CypherParser::ENDS:
      case CypherParser::CONTAINS:
      case CypherParser::IN:
      case CypherParser::IS:
      case CypherParser::CypherNULL:
      case CypherParser::CASE:
      case CypherParser::ELSE:
      case CypherParser::END:
      case CypherParser::WHEN:
      case CypherParser::THEN:
      case CypherParser::EXISTS:
      case CypherParser::TRUE:
      case CypherParser::FALSE:
      case CypherParser::CONSTRAINT:
      case CypherParser::DO:
      case CypherParser::FOR:
      case CypherParser::REQUIRE:
      case CypherParser::UNIQUE:
      case CypherParser::MANDATORY:
      case CypherParser::SCALAR:
      case CypherParser::OF:
      case CypherParser::ADD:
      case CypherParser::DROP: {
        enterOuterAlt(_localctx, 2);
        setState(1589);
        oC_ReservedWord();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_ReservedWordContext ------------------------------------------------------------------

CypherParser::OC_ReservedWordContext::OC_ReservedWordContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ALL() {
  return getToken(CypherParser::ALL, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ASC() {
  return getToken(CypherParser::ASC, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ASCENDING() {
  return getToken(CypherParser::ASCENDING, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::BY() {
  return getToken(CypherParser::BY, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::CREATE() {
  return getToken(CypherParser::CREATE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DELETE() {
  return getToken(CypherParser::DELETE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DESC() {
  return getToken(CypherParser::DESC, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DESCENDING() {
  return getToken(CypherParser::DESCENDING, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DETACH() {
  return getToken(CypherParser::DETACH, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::EXISTS() {
  return getToken(CypherParser::EXISTS, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::LIMIT() {
  return getToken(CypherParser::LIMIT, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::MATCH() {
  return getToken(CypherParser::MATCH, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::MERGE() {
  return getToken(CypherParser::MERGE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ON() {
  return getToken(CypherParser::ON, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::OPTIONAL() {
  return getToken(CypherParser::OPTIONAL, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ORDER() {
  return getToken(CypherParser::ORDER, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::REMOVE() {
  return getToken(CypherParser::REMOVE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::RETURN() {
  return getToken(CypherParser::RETURN, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::SET() {
  return getToken(CypherParser::SET, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::L_SKIP() {
  return getToken(CypherParser::L_SKIP, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::WHERE() {
  return getToken(CypherParser::WHERE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::WITH() {
  return getToken(CypherParser::WITH, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::UNION() {
  return getToken(CypherParser::UNION, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::UNWIND() {
  return getToken(CypherParser::UNWIND, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::AND() {
  return getToken(CypherParser::AND, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::AS() {
  return getToken(CypherParser::AS, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::CONTAINS() {
  return getToken(CypherParser::CONTAINS, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DISTINCT() {
  return getToken(CypherParser::DISTINCT, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ENDS() {
  return getToken(CypherParser::ENDS, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::IN() {
  return getToken(CypherParser::IN, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::IS() {
  return getToken(CypherParser::IS, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::NOT() {
  return getToken(CypherParser::NOT, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::OR() {
  return getToken(CypherParser::OR, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::STARTS() {
  return getToken(CypherParser::STARTS, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::XOR() {
  return getToken(CypherParser::XOR, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::FALSE() {
  return getToken(CypherParser::FALSE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::TRUE() {
  return getToken(CypherParser::TRUE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::CypherNULL() {
  return getToken(CypherParser::CypherNULL, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::CONSTRAINT() {
  return getToken(CypherParser::CONSTRAINT, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DO() {
  return getToken(CypherParser::DO, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::FOR() {
  return getToken(CypherParser::FOR, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::REQUIRE() {
  return getToken(CypherParser::REQUIRE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::UNIQUE() {
  return getToken(CypherParser::UNIQUE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::CASE() {
  return getToken(CypherParser::CASE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::WHEN() {
  return getToken(CypherParser::WHEN, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::THEN() {
  return getToken(CypherParser::THEN, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ELSE() {
  return getToken(CypherParser::ELSE, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::END() {
  return getToken(CypherParser::END, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::MANDATORY() {
  return getToken(CypherParser::MANDATORY, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::SCALAR() {
  return getToken(CypherParser::SCALAR, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::OF() {
  return getToken(CypherParser::OF, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::ADD() {
  return getToken(CypherParser::ADD, 0);
}

tree::TerminalNode* CypherParser::OC_ReservedWordContext::DROP() {
  return getToken(CypherParser::DROP, 0);
}


size_t CypherParser::OC_ReservedWordContext::getRuleIndex() const {
  return CypherParser::RuleOC_ReservedWord;
}

void CypherParser::OC_ReservedWordContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_ReservedWord(this);
}

void CypherParser::OC_ReservedWordContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_ReservedWord(this);
}


antlrcpp::Any CypherParser::OC_ReservedWordContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_ReservedWord(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_ReservedWordContext* CypherParser::oC_ReservedWord() {
  OC_ReservedWordContext *_localctx = _tracker.createInstance<OC_ReservedWordContext>(_ctx, getState());
  enterRule(_localctx, 198, CypherParser::RuleOC_ReservedWord);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1592);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::UNION)
      | (1ULL << CypherParser::ALL)
      | (1ULL << CypherParser::OPTIONAL)
      | (1ULL << CypherParser::MATCH)
      | (1ULL << CypherParser::UNWIND)
      | (1ULL << CypherParser::AS)
      | (1ULL << CypherParser::MERGE)
      | (1ULL << CypherParser::ON)
      | (1ULL << CypherParser::CREATE)
      | (1ULL << CypherParser::SET)
      | (1ULL << CypherParser::DETACH)
      | (1ULL << CypherParser::DELETE)
      | (1ULL << CypherParser::REMOVE)
      | (1ULL << CypherParser::WITH)
      | (1ULL << CypherParser::RETURN)
      | (1ULL << CypherParser::DISTINCT))) != 0) || ((((_la - 64) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 64)) & ((1ULL << (CypherParser::ORDER - 64))
      | (1ULL << (CypherParser::BY - 64))
      | (1ULL << (CypherParser::L_SKIP - 64))
      | (1ULL << (CypherParser::LIMIT - 64))
      | (1ULL << (CypherParser::ASCENDING - 64))
      | (1ULL << (CypherParser::ASC - 64))
      | (1ULL << (CypherParser::DESCENDING - 64))
      | (1ULL << (CypherParser::DESC - 64))
      | (1ULL << (CypherParser::WHERE - 64))
      | (1ULL << (CypherParser::OR - 64))
      | (1ULL << (CypherParser::XOR - 64))
      | (1ULL << (CypherParser::AND - 64))
      | (1ULL << (CypherParser::NOT - 64))
      | (1ULL << (CypherParser::STARTS - 64))
      | (1ULL << (CypherParser::ENDS - 64))
      | (1ULL << (CypherParser::CONTAINS - 64))
      | (1ULL << (CypherParser::IN - 64))
      | (1ULL << (CypherParser::IS - 64))
      | (1ULL << (CypherParser::CypherNULL - 64))
      | (1ULL << (CypherParser::CASE - 64))
      | (1ULL << (CypherParser::ELSE - 64))
      | (1ULL << (CypherParser::END - 64))
      | (1ULL << (CypherParser::WHEN - 64))
      | (1ULL << (CypherParser::THEN - 64))
      | (1ULL << (CypherParser::EXISTS - 64))
      | (1ULL << (CypherParser::TRUE - 64))
      | (1ULL << (CypherParser::FALSE - 64))
      | (1ULL << (CypherParser::CONSTRAINT - 64))
      | (1ULL << (CypherParser::DO - 64))
      | (1ULL << (CypherParser::FOR - 64))
      | (1ULL << (CypherParser::REQUIRE - 64))
      | (1ULL << (CypherParser::UNIQUE - 64))
      | (1ULL << (CypherParser::MANDATORY - 64))
      | (1ULL << (CypherParser::SCALAR - 64))
      | (1ULL << (CypherParser::OF - 64))
      | (1ULL << (CypherParser::ADD - 64))
      | (1ULL << (CypherParser::DROP - 64)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_SymbolicNameContext ------------------------------------------------------------------

CypherParser::OC_SymbolicNameContext::OC_SymbolicNameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::UnescapedSymbolicName() {
  return getToken(CypherParser::UnescapedSymbolicName, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::EscapedSymbolicName() {
  return getToken(CypherParser::EscapedSymbolicName, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::HexLetter() {
  return getToken(CypherParser::HexLetter, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::COUNT() {
  return getToken(CypherParser::COUNT, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::FILTER() {
  return getToken(CypherParser::FILTER, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::EXTRACT() {
  return getToken(CypherParser::EXTRACT, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::ANY() {
  return getToken(CypherParser::ANY, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::NONE() {
  return getToken(CypherParser::NONE, 0);
}

tree::TerminalNode* CypherParser::OC_SymbolicNameContext::SINGLE() {
  return getToken(CypherParser::SINGLE, 0);
}


size_t CypherParser::OC_SymbolicNameContext::getRuleIndex() const {
  return CypherParser::RuleOC_SymbolicName;
}

void CypherParser::OC_SymbolicNameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_SymbolicName(this);
}

void CypherParser::OC_SymbolicNameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_SymbolicName(this);
}


antlrcpp::Any CypherParser::OC_SymbolicNameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_SymbolicName(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_SymbolicNameContext* CypherParser::oC_SymbolicName() {
  OC_SymbolicNameContext *_localctx = _tracker.createInstance<OC_SymbolicNameContext>(_ctx, getState());
  enterRule(_localctx, 200, CypherParser::RuleOC_SymbolicName);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1594);
    _la = _input->LA(1);
    if (!(((((_la - 83) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 83)) & ((1ULL << (CypherParser::COUNT - 83))
      | (1ULL << (CypherParser::ANY - 83))
      | (1ULL << (CypherParser::NONE - 83))
      | (1ULL << (CypherParser::SINGLE - 83))
      | (1ULL << (CypherParser::HexLetter - 83))
      | (1ULL << (CypherParser::FILTER - 83))
      | (1ULL << (CypherParser::EXTRACT - 83))
      | (1ULL << (CypherParser::UnescapedSymbolicName - 83))
      | (1ULL << (CypherParser::EscapedSymbolicName - 83)))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_LeftArrowHeadContext ------------------------------------------------------------------

CypherParser::OC_LeftArrowHeadContext::OC_LeftArrowHeadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CypherParser::OC_LeftArrowHeadContext::getRuleIndex() const {
  return CypherParser::RuleOC_LeftArrowHead;
}

void CypherParser::OC_LeftArrowHeadContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_LeftArrowHead(this);
}

void CypherParser::OC_LeftArrowHeadContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_LeftArrowHead(this);
}


antlrcpp::Any CypherParser::OC_LeftArrowHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_LeftArrowHead(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_LeftArrowHeadContext* CypherParser::oC_LeftArrowHead() {
  OC_LeftArrowHeadContext *_localctx = _tracker.createInstance<OC_LeftArrowHeadContext>(_ctx, getState());
  enterRule(_localctx, 202, CypherParser::RuleOC_LeftArrowHead);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1596);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::T__13)
      | (1ULL << CypherParser::T__26)
      | (1ULL << CypherParser::T__27)
      | (1ULL << CypherParser::T__28)
      | (1ULL << CypherParser::T__29))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_RightArrowHeadContext ------------------------------------------------------------------

CypherParser::OC_RightArrowHeadContext::OC_RightArrowHeadContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CypherParser::OC_RightArrowHeadContext::getRuleIndex() const {
  return CypherParser::RuleOC_RightArrowHead;
}

void CypherParser::OC_RightArrowHeadContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_RightArrowHead(this);
}

void CypherParser::OC_RightArrowHeadContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_RightArrowHead(this);
}


antlrcpp::Any CypherParser::OC_RightArrowHeadContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_RightArrowHead(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_RightArrowHeadContext* CypherParser::oC_RightArrowHead() {
  OC_RightArrowHeadContext *_localctx = _tracker.createInstance<OC_RightArrowHeadContext>(_ctx, getState());
  enterRule(_localctx, 204, CypherParser::RuleOC_RightArrowHead);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1598);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::T__14)
      | (1ULL << CypherParser::T__30)
      | (1ULL << CypherParser::T__31)
      | (1ULL << CypherParser::T__32)
      | (1ULL << CypherParser::T__33))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- OC_DashContext ------------------------------------------------------------------

CypherParser::OC_DashContext::OC_DashContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CypherParser::OC_DashContext::getRuleIndex() const {
  return CypherParser::RuleOC_Dash;
}

void CypherParser::OC_DashContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterOC_Dash(this);
}

void CypherParser::OC_DashContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CypherListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitOC_Dash(this);
}


antlrcpp::Any CypherParser::OC_DashContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CypherVisitor*>(visitor))
    return parserVisitor->visitOC_Dash(this);
  else
    return visitor->visitChildren(this);
}

CypherParser::OC_DashContext* CypherParser::oC_Dash() {
  OC_DashContext *_localctx = _tracker.createInstance<OC_DashContext>(_ctx, getState());
  enterRule(_localctx, 206, CypherParser::RuleOC_Dash);
  size_t _la = 0;

  auto onExit = finally([=] {
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(1600);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CypherParser::T__18)
      | (1ULL << CypherParser::T__34)
      | (1ULL << CypherParser::T__35)
      | (1ULL << CypherParser::T__36)
      | (1ULL << CypherParser::T__37)
      | (1ULL << CypherParser::T__38)
      | (1ULL << CypherParser::T__39)
      | (1ULL << CypherParser::T__40)
      | (1ULL << CypherParser::T__41)
      | (1ULL << CypherParser::T__42)
      | (1ULL << CypherParser::T__43)
      | (1ULL << CypherParser::T__44))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

// Static vars and initialization.
std::vector<dfa::DFA> CypherParser::_decisionToDFA;
atn::PredictionContextCache CypherParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CypherParser::_atn;
std::vector<uint16_t> CypherParser::_serializedATN;

std::vector<std::string> CypherParser::_ruleNames = {
  "oC_Cypher", "oC_Statement", "oC_Query", "oC_RegularQuery", "oC_Union", 
  "oC_SingleQuery", "oC_SinglePartQuery", "oC_MultiPartQuery", "oC_UpdatingClause", 
  "oC_ReadingClause", "oC_Match", "oC_Unwind", "oC_Merge", "oC_MergeAction", 
  "oC_Create", "oC_Set", "oC_SetItem", "oC_Delete", "oC_Remove", "oC_RemoveItem", 
  "oC_InQueryCall", "oC_StandaloneCall", "oC_YieldItems", "oC_YieldItem", 
  "oC_With", "oC_Return", "oC_ProjectionBody", "oC_ProjectionItems", "oC_ProjectionItem", 
  "oC_Order", "oC_Skip", "oC_Limit", "oC_SortItem", "oC_Where", "oC_Pattern", 
  "oC_PatternPart", "oC_AnonymousPatternPart", "oC_ShortestPathPattern", 
  "oC_PatternElement", "oC_RelationshipsPattern", "oC_NodePattern", "oC_PatternElementChain", 
  "oC_RelationshipPattern", "oC_RelationshipDetail", "oC_Properties", "oC_RelationshipTypes", 
  "oC_NodeLabels", "oC_NodeLabel", "oC_RangeLiteral", "oC_LabelName", "oC_RelTypeName", 
  "oC_PropertyExpression", "oC_Expression", "oC_OrExpression", "oC_XorExpression", 
  "oC_AndExpression", "oC_NotExpression", "oC_ComparisonExpression", "oC_PartialComparisonExpression", 
  "oC_StringListNullPredicateExpression", "oC_StringPredicateExpression", 
  "oC_ListPredicateExpression", "oC_NullPredicateExpression", "oC_AddOrSubtractExpression", 
  "oC_MultiplyDivideModuloExpression", "oC_PowerOfExpression", "oC_UnaryAddOrSubtractExpression", 
  "oC_ListOperatorExpression", "oC_PropertyOrLabelsExpression", "oC_PropertyLookup", 
  "oC_Atom", "oC_CaseExpression", "oC_CaseAlternative", "oC_ListComprehension", 
  "oC_PatternComprehension", "oC_Quantifier", "oC_FilterExpression", "oC_PatternPredicate", 
  "oC_ParenthesizedExpression", "oC_IdInColl", "oC_FunctionInvocation", 
  "oC_FunctionName", "oC_ExistentialSubquery", "oC_ExplicitProcedureInvocation", 
  "oC_ImplicitProcedureInvocation", "oC_ProcedureResultField", "oC_ProcedureName", 
  "oC_Namespace", "oC_Variable", "oC_Literal", "oC_BooleanLiteral", "oC_NumberLiteral", 
  "oC_IntegerLiteral", "oC_DoubleLiteral", "oC_ListLiteral", "oC_MapLiteral", 
  "oC_PropertyKeyName", "oC_Parameter", "oC_SchemaName", "oC_ReservedWord", 
  "oC_SymbolicName", "oC_LeftArrowHead", "oC_RightArrowHead", "oC_Dash"
};

std::vector<std::string> CypherParser::_literalNames = {
  "", "';'", "','", "'='", "'+='", "'*'", "'('", "')'", "'['", "']'", "':'", 
  "'|'", "'..'", "'<>'", "'<'", "'>'", "'<='", "'>='", "'+'", "'-'", "'/'", 
  "'%'", "'^'", "'.'", "'{'", "'}'", "'$'", "'\u27E8'", "'\u3008'", "'\uFE64'", 
  "'\uFF1C'", "'\u27E9'", "'\u3009'", "'\uFE65'", "'\uFF1E'", "'\u00AD'", 
  "'\u2010'", "'\u2011'", "'\u2012'", "'\u2013'", "'\u2014'", "'\u2015'", 
  "'\u2212'", "'\uFE58'", "'\uFE63'", "'\uFF0D'", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "'0'"
};

std::vector<std::string> CypherParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "", "", "UNION", "ALL", "OPTIONAL", "MATCH", 
  "UNWIND", "AS", "MERGE", "ON", "CREATE", "SET", "DETACH", "DELETE", "REMOVE", 
  "CALL", "YIELD", "WITH", "RETURN", "DISTINCT", "ORDER", "BY", "L_SKIP", 
  "LIMIT", "ASCENDING", "ASC", "DESCENDING", "DESC", "WHERE", "OR", "XOR", 
  "AND", "NOT", "STARTS", "ENDS", "CONTAINS", "IN", "IS", "NULL", "COUNT", 
  "CASE", "ELSE", "END", "WHEN", "THEN", "ANY", "NONE", "SINGLE", "EXISTS", 
  "TRUE", "FALSE", "HexInteger", "DecimalInteger", "OctalInteger", "HexLetter", 
  "HexDigit", "Digit", "NonZeroDigit", "NonZeroOctDigit", "OctDigit", "ZeroDigit", 
  "ExponentDecimalReal", "RegularDecimalReal", "StringLiteral", "EscapedChar", 
  "CONSTRAINT", "DO", "FOR", "REQUIRE", "UNIQUE", "MANDATORY", "SCALAR", 
  "OF", "ADD", "DROP", "FILTER", "EXTRACT", "UnescapedSymbolicName", "IdentifierStart", 
  "IdentifierPart", "EscapedSymbolicName", "SP", "WHITESPACE", "Comment"
};

dfa::Vocabulary CypherParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CypherParser::_tokenNames;

CypherParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x81, 0x645, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x4, 
    0x1f, 0x9, 0x1f, 0x4, 0x20, 0x9, 0x20, 0x4, 0x21, 0x9, 0x21, 0x4, 0x22, 
    0x9, 0x22, 0x4, 0x23, 0x9, 0x23, 0x4, 0x24, 0x9, 0x24, 0x4, 0x25, 0x9, 
    0x25, 0x4, 0x26, 0x9, 0x26, 0x4, 0x27, 0x9, 0x27, 0x4, 0x28, 0x9, 0x28, 
    0x4, 0x29, 0x9, 0x29, 0x4, 0x2a, 0x9, 0x2a, 0x4, 0x2b, 0x9, 0x2b, 0x4, 
    0x2c, 0x9, 0x2c, 0x4, 0x2d, 0x9, 0x2d, 0x4, 0x2e, 0x9, 0x2e, 0x4, 0x2f, 
    0x9, 0x2f, 0x4, 0x30, 0x9, 0x30, 0x4, 0x31, 0x9, 0x31, 0x4, 0x32, 0x9, 
    0x32, 0x4, 0x33, 0x9, 0x33, 0x4, 0x34, 0x9, 0x34, 0x4, 0x35, 0x9, 0x35, 
    0x4, 0x36, 0x9, 0x36, 0x4, 0x37, 0x9, 0x37, 0x4, 0x38, 0x9, 0x38, 0x4, 
    0x39, 0x9, 0x39, 0x4, 0x3a, 0x9, 0x3a, 0x4, 0x3b, 0x9, 0x3b, 0x4, 0x3c, 
    0x9, 0x3c, 0x4, 0x3d, 0x9, 0x3d, 0x4, 0x3e, 0x9, 0x3e, 0x4, 0x3f, 0x9, 
    0x3f, 0x4, 0x40, 0x9, 0x40, 0x4, 0x41, 0x9, 0x41, 0x4, 0x42, 0x9, 0x42, 
    0x4, 0x43, 0x9, 0x43, 0x4, 0x44, 0x9, 0x44, 0x4, 0x45, 0x9, 0x45, 0x4, 
    0x46, 0x9, 0x46, 0x4, 0x47, 0x9, 0x47, 0x4, 0x48, 0x9, 0x48, 0x4, 0x49, 
    0x9, 0x49, 0x4, 0x4a, 0x9, 0x4a, 0x4, 0x4b, 0x9, 0x4b, 0x4, 0x4c, 0x9, 
    0x4c, 0x4, 0x4d, 0x9, 0x4d, 0x4, 0x4e, 0x9, 0x4e, 0x4, 0x4f, 0x9, 0x4f, 
    0x4, 0x50, 0x9, 0x50, 0x4, 0x51, 0x9, 0x51, 0x4, 0x52, 0x9, 0x52, 0x4, 
    0x53, 0x9, 0x53, 0x4, 0x54, 0x9, 0x54, 0x4, 0x55, 0x9, 0x55, 0x4, 0x56, 
    0x9, 0x56, 0x4, 0x57, 0x9, 0x57, 0x4, 0x58, 0x9, 0x58, 0x4, 0x59, 0x9, 
    0x59, 0x4, 0x5a, 0x9, 0x5a, 0x4, 0x5b, 0x9, 0x5b, 0x4, 0x5c, 0x9, 0x5c, 
    0x4, 0x5d, 0x9, 0x5d, 0x4, 0x5e, 0x9, 0x5e, 0x4, 0x5f, 0x9, 0x5f, 0x4, 
    0x60, 0x9, 0x60, 0x4, 0x61, 0x9, 0x61, 0x4, 0x62, 0x9, 0x62, 0x4, 0x63, 
    0x9, 0x63, 0x4, 0x64, 0x9, 0x64, 0x4, 0x65, 0x9, 0x65, 0x4, 0x66, 0x9, 
    0x66, 0x4, 0x67, 0x9, 0x67, 0x4, 0x68, 0x9, 0x68, 0x4, 0x69, 0x9, 0x69, 
    0x3, 0x2, 0x5, 0x2, 0xd4, 0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x5, 0x2, 0xd8, 
    0xa, 0x2, 0x3, 0x2, 0x5, 0x2, 0xdb, 0xa, 0x2, 0x3, 0x2, 0x5, 0x2, 0xde, 
    0xa, 0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 
    0x5, 0x4, 0xe6, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0xea, 0xa, 0x5, 
    0x3, 0x5, 0x7, 0x5, 0xed, 0xa, 0x5, 0xc, 0x5, 0xe, 0x5, 0xf0, 0xb, 0x5, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0xf6, 0xa, 0x6, 0x3, 
    0x6, 0x3, 0x6, 0x3, 0x6, 0x5, 0x6, 0xfb, 0xa, 0x6, 0x3, 0x6, 0x5, 0x6, 
    0xfe, 0xa, 0x6, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x102, 0xa, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x5, 0x8, 0x106, 0xa, 0x8, 0x7, 0x8, 0x108, 0xa, 0x8, 
    0xc, 0x8, 0xe, 0x8, 0x10b, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 
    0x8, 0x110, 0xa, 0x8, 0x7, 0x8, 0x112, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 
    0x115, 0xb, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x119, 0xa, 0x8, 0x3, 
    0x8, 0x7, 0x8, 0x11c, 0xa, 0x8, 0xc, 0x8, 0xe, 0x8, 0x11f, 0xb, 0x8, 
    0x3, 0x8, 0x5, 0x8, 0x122, 0xa, 0x8, 0x3, 0x8, 0x5, 0x8, 0x125, 0xa, 
    0x8, 0x5, 0x8, 0x127, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x12b, 
    0xa, 0x9, 0x7, 0x9, 0x12d, 0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x130, 0xb, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x134, 0xa, 0x9, 0x7, 0x9, 0x136, 
    0xa, 0x9, 0xc, 0x9, 0xe, 0x9, 0x139, 0xb, 0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 
    0x9, 0x13d, 0xa, 0x9, 0x6, 0x9, 0x13f, 0xa, 0x9, 0xd, 0x9, 0xe, 0x9, 
    0x140, 0x3, 0x9, 0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 
    0xa, 0x5, 0xa, 0x14a, 0xa, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 
    0x14f, 0xa, 0xb, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x153, 0xa, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x5, 0xc, 0x157, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 
    0x15b, 0xa, 0xc, 0x3, 0xc, 0x5, 0xc, 0x15e, 0xa, 0xc, 0x3, 0xd, 0x3, 
    0xd, 0x5, 0xd, 0x162, 0xa, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 
    0x3, 0xd, 0x3, 0xd, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x16c, 0xa, 0xe, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x7, 0xe, 0x171, 0xa, 0xe, 0xc, 0xe, 0xe, 0xe, 
    0x174, 0xb, 0xe, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 
    0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0xf, 0x5, 0xf, 0x180, 0xa, 0xf, 
    0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 0x184, 0xa, 0x10, 0x3, 0x10, 0x3, 0x10, 
    0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x18a, 0xa, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x5, 0x11, 0x18e, 0xa, 0x11, 0x3, 0x11, 0x3, 0x11, 0x5, 0x11, 0x192, 
    0xa, 0x11, 0x3, 0x11, 0x7, 0x11, 0x195, 0xa, 0x11, 0xc, 0x11, 0xe, 0x11, 
    0x198, 0xb, 0x11, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x19c, 0xa, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x1a0, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x1a6, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x5, 0x12, 0x1aa, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 
    0x5, 0x12, 0x1b0, 0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x1b4, 
    0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x1ba, 
    0xa, 0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0x1be, 0xa, 0x12, 0x3, 0x13, 
    0x3, 0x13, 0x5, 0x13, 0x1c2, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 
    0x1c6, 0xa, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x1ca, 0xa, 0x13, 
    0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0x1ce, 0xa, 0x13, 0x3, 0x13, 0x7, 0x13, 
    0x1d1, 0xa, 0x13, 0xc, 0x13, 0xe, 0x13, 0x1d4, 0xb, 0x13, 0x3, 0x14, 
    0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 0x1da, 0xa, 0x14, 0x3, 0x14, 
    0x3, 0x14, 0x5, 0x14, 0x1de, 0xa, 0x14, 0x3, 0x14, 0x7, 0x14, 0x1e1, 
    0xa, 0x14, 0xc, 0x14, 0xe, 0x14, 0x1e4, 0xb, 0x14, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x3, 0x15, 0x5, 0x15, 0x1ea, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x3, 0x16, 0x5, 0x16, 0x1f0, 0xa, 0x16, 0x3, 0x16, 0x3, 0x16, 
    0x3, 0x16, 0x5, 0x16, 0x1f5, 0xa, 0x16, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 
    0x3, 0x17, 0x5, 0x17, 0x1fb, 0xa, 0x17, 0x3, 0x17, 0x5, 0x17, 0x1fe, 
    0xa, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x5, 0x17, 0x204, 
    0xa, 0x17, 0x5, 0x17, 0x206, 0xa, 0x17, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 
    0x20a, 0xa, 0x18, 0x3, 0x18, 0x3, 0x18, 0x5, 0x18, 0x20e, 0xa, 0x18, 
    0x3, 0x18, 0x7, 0x18, 0x211, 0xa, 0x18, 0xc, 0x18, 0xe, 0x18, 0x214, 
    0xb, 0x18, 0x3, 0x18, 0x5, 0x18, 0x217, 0xa, 0x18, 0x3, 0x18, 0x5, 0x18, 
    0x21a, 0xa, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 
    0x5, 0x19, 0x221, 0xa, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x1a, 0x3, 0x1a, 
    0x3, 0x1a, 0x5, 0x1a, 0x228, 0xa, 0x1a, 0x3, 0x1a, 0x5, 0x1a, 0x22b, 
    0xa, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1c, 0x5, 0x1c, 0x231, 
    0xa, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x234, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x23a, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x5, 0x1c, 0x23e, 0xa, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x5, 0x1c, 0x242, 
    0xa, 0x1c, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x246, 0xa, 0x1d, 0x3, 0x1d, 
    0x3, 0x1d, 0x5, 0x1d, 0x24a, 0xa, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 0x24d, 
    0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 0x250, 0xb, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 
    0x5, 0x1d, 0x254, 0xa, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x258, 
    0xa, 0x1d, 0x3, 0x1d, 0x7, 0x1d, 0x25b, 0xa, 0x1d, 0xc, 0x1d, 0xe, 0x1d, 
    0x25e, 0xb, 0x1d, 0x5, 0x1d, 0x260, 0xa, 0x1d, 0x3, 0x1e, 0x3, 0x1e, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x5, 0x1e, 0x269, 
    0xa, 0x1e, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 0x1f, 0x3, 
    0x1f, 0x3, 0x1f, 0x5, 0x1f, 0x272, 0xa, 0x1f, 0x3, 0x1f, 0x7, 0x1f, 
    0x275, 0xa, 0x1f, 0xc, 0x1f, 0xe, 0x1f, 0x278, 0xb, 0x1f, 0x3, 0x20, 
    0x3, 0x20, 0x3, 0x20, 0x3, 0x20, 0x3, 0x21, 0x3, 0x21, 0x3, 0x21, 0x3, 
    0x21, 0x3, 0x22, 0x3, 0x22, 0x5, 0x22, 0x284, 0xa, 0x22, 0x3, 0x22, 
    0x5, 0x22, 0x287, 0xa, 0x22, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 0x3, 0x23, 
    0x3, 0x24, 0x3, 0x24, 0x5, 0x24, 0x28f, 0xa, 0x24, 0x3, 0x24, 0x3, 0x24, 
    0x5, 0x24, 0x293, 0xa, 0x24, 0x3, 0x24, 0x7, 0x24, 0x296, 0xa, 0x24, 
    0xc, 0x24, 0xe, 0x24, 0x299, 0xb, 0x24, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 
    0x29d, 0xa, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x2a1, 0xa, 0x25, 
    0x3, 0x25, 0x3, 0x25, 0x3, 0x25, 0x5, 0x25, 0x2a6, 0xa, 0x25, 0x3, 0x26, 
    0x3, 0x26, 0x5, 0x26, 0x2aa, 0xa, 0x26, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 
    0x2ae, 0xa, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x2b2, 0xa, 0x27, 
    0x3, 0x27, 0x3, 0x27, 0x3, 0x27, 0x5, 0x27, 0x2b7, 0xa, 0x27, 0x3, 0x28, 
    0x3, 0x28, 0x5, 0x28, 0x2bb, 0xa, 0x28, 0x3, 0x28, 0x7, 0x28, 0x2be, 
    0xa, 0x28, 0xc, 0x28, 0xe, 0x28, 0x2c1, 0xb, 0x28, 0x3, 0x28, 0x3, 0x28, 
    0x5, 0x28, 0x2c5, 0xa, 0x28, 0x3, 0x28, 0x3, 0x28, 0x3, 0x28, 0x5, 0x28, 
    0x2ca, 0xa, 0x28, 0x5, 0x28, 0x2cc, 0xa, 0x28, 0x3, 0x29, 0x3, 0x29, 
    0x5, 0x29, 0x2d0, 0xa, 0x29, 0x3, 0x29, 0x6, 0x29, 0x2d3, 0xa, 0x29, 
    0xd, 0x29, 0xe, 0x29, 0x2d4, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x2d9, 
    0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x2dd, 0xa, 0x2a, 0x5, 0x2a, 
    0x2df, 0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x2e3, 0xa, 0x2a, 
    0x5, 0x2a, 0x2e5, 0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x5, 0x2a, 0x2e9, 
    0xa, 0x2a, 0x5, 0x2a, 0x2eb, 0xa, 0x2a, 0x3, 0x2a, 0x3, 0x2a, 0x3, 0x2b, 
    0x3, 0x2b, 0x5, 0x2b, 0x2f1, 0xa, 0x2b, 0x3, 0x2b, 0x3, 0x2b, 0x3, 0x2c, 
    0x3, 0x2c, 0x5, 0x2c, 0x2f7, 0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 
    0x2fb, 0xa, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x2fe, 0xa, 0x2c, 0x3, 0x2c, 
    0x5, 0x2c, 0x301, 0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x305, 
    0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x30b, 
    0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x30f, 0xa, 0x2c, 0x3, 0x2c, 
    0x5, 0x2c, 0x312, 0xa, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x315, 0xa, 0x2c, 
    0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x31b, 0xa, 0x2c, 
    0x3, 0x2c, 0x5, 0x2c, 0x31e, 0xa, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x321, 
    0xa, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x325, 0xa, 0x2c, 0x3, 0x2c, 
    0x3, 0x2c, 0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x32b, 0xa, 0x2c, 0x3, 0x2c, 
    0x5, 0x2c, 0x32e, 0xa, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x331, 0xa, 0x2c, 
    0x3, 0x2c, 0x3, 0x2c, 0x5, 0x2c, 0x335, 0xa, 0x2c, 0x3, 0x2d, 0x3, 0x2d, 
    0x5, 0x2d, 0x339, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x33d, 
    0xa, 0x2d, 0x5, 0x2d, 0x33f, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 
    0x343, 0xa, 0x2d, 0x5, 0x2d, 0x345, 0xa, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 
    0x348, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x5, 0x2d, 0x34c, 0xa, 0x2d, 
    0x5, 0x2d, 0x34e, 0xa, 0x2d, 0x3, 0x2d, 0x3, 0x2d, 0x3, 0x2e, 0x3, 0x2e, 
    0x5, 0x2e, 0x354, 0xa, 0x2e, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x358, 
    0xa, 0x2f, 0x3, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x35c, 0xa, 0x2f, 0x3, 0x2f, 
    0x3, 0x2f, 0x5, 0x2f, 0x360, 0xa, 0x2f, 0x3, 0x2f, 0x5, 0x2f, 0x363, 
    0xa, 0x2f, 0x3, 0x2f, 0x7, 0x2f, 0x366, 0xa, 0x2f, 0xc, 0x2f, 0xe, 0x2f, 
    0x369, 0xb, 0x2f, 0x3, 0x30, 0x3, 0x30, 0x5, 0x30, 0x36d, 0xa, 0x30, 
    0x3, 0x30, 0x7, 0x30, 0x370, 0xa, 0x30, 0xc, 0x30, 0xe, 0x30, 0x373, 
    0xb, 0x30, 0x3, 0x31, 0x3, 0x31, 0x5, 0x31, 0x377, 0xa, 0x31, 0x3, 0x31, 
    0x3, 0x31, 0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x37d, 0xa, 0x32, 0x3, 0x32, 
    0x3, 0x32, 0x5, 0x32, 0x381, 0xa, 0x32, 0x5, 0x32, 0x383, 0xa, 0x32, 
    0x3, 0x32, 0x3, 0x32, 0x5, 0x32, 0x387, 0xa, 0x32, 0x3, 0x32, 0x3, 0x32, 
    0x5, 0x32, 0x38b, 0xa, 0x32, 0x5, 0x32, 0x38d, 0xa, 0x32, 0x5, 0x32, 
    0x38f, 0xa, 0x32, 0x3, 0x33, 0x3, 0x33, 0x3, 0x34, 0x3, 0x34, 0x3, 0x35, 
    0x3, 0x35, 0x5, 0x35, 0x397, 0xa, 0x35, 0x3, 0x35, 0x6, 0x35, 0x39a, 
    0xa, 0x35, 0xd, 0x35, 0xe, 0x35, 0x39b, 0x3, 0x36, 0x3, 0x36, 0x3, 0x37, 
    0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x3, 0x37, 0x7, 0x37, 0x3a5, 0xa, 0x37, 
    0xc, 0x37, 0xe, 0x37, 0x3a8, 0xb, 0x37, 0x3, 0x38, 0x3, 0x38, 0x3, 0x38, 
    0x3, 0x38, 0x3, 0x38, 0x7, 0x38, 0x3af, 0xa, 0x38, 0xc, 0x38, 0xe, 0x38, 
    0x3b2, 0xb, 0x38, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 0x3, 0x39, 
    0x7, 0x39, 0x3b9, 0xa, 0x39, 0xc, 0x39, 0xe, 0x39, 0x3bc, 0xb, 0x39, 
    0x3, 0x3a, 0x3, 0x3a, 0x5, 0x3a, 0x3c0, 0xa, 0x3a, 0x7, 0x3a, 0x3c2, 
    0xa, 0x3a, 0xc, 0x3a, 0xe, 0x3a, 0x3c5, 0xb, 0x3a, 0x3, 0x3a, 0x3, 0x3a, 
    0x3, 0x3b, 0x3, 0x3b, 0x5, 0x3b, 0x3cb, 0xa, 0x3b, 0x3, 0x3b, 0x7, 0x3b, 
    0x3ce, 0xa, 0x3b, 0xc, 0x3b, 0xe, 0x3b, 0x3d1, 0xb, 0x3b, 0x3, 0x3c, 
    0x3, 0x3c, 0x5, 0x3c, 0x3d5, 0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 
    0x5, 0x3c, 0x3da, 0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 
    0x3df, 0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x3e4, 
    0xa, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x3e9, 0xa, 0x3c, 
    0x3, 0x3c, 0x3, 0x3c, 0x3, 0x3c, 0x5, 0x3c, 0x3ee, 0xa, 0x3c, 0x3, 0x3c, 
    0x5, 0x3c, 0x3f1, 0xa, 0x3c, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 0x3, 0x3d, 
    0x7, 0x3d, 0x3f7, 0xa, 0x3d, 0xc, 0x3d, 0xe, 0x3d, 0x3fa, 0xb, 0x3d, 
    0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 
    0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x5, 0x3e, 0x406, 0xa, 0x3e, 
    0x3, 0x3e, 0x5, 0x3e, 0x409, 0xa, 0x3e, 0x3, 0x3e, 0x3, 0x3e, 0x3, 0x3f, 
    0x3, 0x3f, 0x3, 0x3f, 0x5, 0x3f, 0x410, 0xa, 0x3f, 0x3, 0x3f, 0x3, 0x3f, 
    0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 
    0x40, 0x3, 0x40, 0x3, 0x40, 0x3, 0x40, 0x5, 0x40, 0x41e, 0xa, 0x40, 
    0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x422, 0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 
    0x5, 0x41, 0x426, 0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x42a, 
    0xa, 0x41, 0x3, 0x41, 0x3, 0x41, 0x5, 0x41, 0x42e, 0xa, 0x41, 0x3, 0x41, 
    0x7, 0x41, 0x431, 0xa, 0x41, 0xc, 0x41, 0xe, 0x41, 0x434, 0xb, 0x41, 
    0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x438, 0xa, 0x42, 0x3, 0x42, 0x3, 0x42, 
    0x5, 0x42, 0x43c, 0xa, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x440, 
    0xa, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 0x444, 0xa, 0x42, 0x3, 0x42, 
    0x3, 0x42, 0x5, 0x42, 0x448, 0xa, 0x42, 0x3, 0x42, 0x3, 0x42, 0x5, 0x42, 
    0x44c, 0xa, 0x42, 0x3, 0x42, 0x7, 0x42, 0x44f, 0xa, 0x42, 0xc, 0x42, 
    0xe, 0x42, 0x452, 0xb, 0x42, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 0x456, 
    0xa, 0x43, 0x3, 0x43, 0x3, 0x43, 0x5, 0x43, 0x45a, 0xa, 0x43, 0x3, 0x43, 
    0x7, 0x43, 0x45d, 0xa, 0x43, 0xc, 0x43, 0xe, 0x43, 0x460, 0xb, 0x43, 
    0x3, 0x44, 0x3, 0x44, 0x3, 0x44, 0x5, 0x44, 0x465, 0xa, 0x44, 0x3, 0x44, 
    0x5, 0x44, 0x468, 0xa, 0x44, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x46c, 
    0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 
    0x45, 0x473, 0xa, 0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x477, 0xa, 
    0x45, 0x3, 0x45, 0x3, 0x45, 0x5, 0x45, 0x47b, 0xa, 0x45, 0x3, 0x45, 
    0x7, 0x45, 0x47e, 0xa, 0x45, 0xc, 0x45, 0xe, 0x45, 0x481, 0xb, 0x45, 
    0x3, 0x46, 0x3, 0x46, 0x5, 0x46, 0x485, 0xa, 0x46, 0x3, 0x46, 0x7, 0x46, 
    0x488, 0xa, 0x46, 0xc, 0x46, 0xe, 0x46, 0x48b, 0xb, 0x46, 0x3, 0x46, 
    0x5, 0x46, 0x48e, 0xa, 0x46, 0x3, 0x46, 0x5, 0x46, 0x491, 0xa, 0x46, 
    0x3, 0x47, 0x3, 0x47, 0x5, 0x47, 0x495, 0xa, 0x47, 0x3, 0x47, 0x3, 0x47, 
    0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 0x49e, 
    0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x5, 0x48, 0x4a2, 0xa, 0x48, 0x3, 0x48, 
    0x3, 0x48, 0x5, 0x48, 0x4a6, 0xa, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 
    0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x3, 0x48, 0x5, 
    0x48, 0x4b1, 0xa, 0x48, 0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 0x4b5, 0xa, 
    0x49, 0x3, 0x49, 0x6, 0x49, 0x4b8, 0xa, 0x49, 0xd, 0x49, 0xe, 0x49, 
    0x4b9, 0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 0x4be, 0xa, 0x49, 0x3, 0x49, 
    0x3, 0x49, 0x5, 0x49, 0x4c2, 0xa, 0x49, 0x3, 0x49, 0x6, 0x49, 0x4c5, 
    0xa, 0x49, 0xd, 0x49, 0xe, 0x49, 0x4c6, 0x5, 0x49, 0x4c9, 0xa, 0x49, 
    0x3, 0x49, 0x5, 0x49, 0x4cc, 0xa, 0x49, 0x3, 0x49, 0x3, 0x49, 0x5, 0x49, 
    0x4d0, 0xa, 0x49, 0x3, 0x49, 0x5, 0x49, 0x4d3, 0xa, 0x49, 0x3, 0x49, 
    0x5, 0x49, 0x4d6, 0xa, 0x49, 0x3, 0x49, 0x3, 0x49, 0x3, 0x4a, 0x3, 0x4a, 
    0x5, 0x4a, 0x4dc, 0xa, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x4e0, 
    0xa, 0x4a, 0x3, 0x4a, 0x3, 0x4a, 0x5, 0x4a, 0x4e4, 0xa, 0x4a, 0x3, 0x4a, 
    0x3, 0x4a, 0x3, 0x4b, 0x3, 0x4b, 0x5, 0x4b, 0x4ea, 0xa, 0x4b, 0x3, 0x4b, 
    0x3, 0x4b, 0x5, 0x4b, 0x4ee, 0xa, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x5, 0x4b, 
    0x4f2, 0xa, 0x4b, 0x3, 0x4b, 0x5, 0x4b, 0x4f5, 0xa, 0x4b, 0x3, 0x4b, 
    0x5, 0x4b, 0x4f8, 0xa, 0x4b, 0x3, 0x4b, 0x3, 0x4b, 0x3, 0x4c, 0x3, 0x4c, 
    0x5, 0x4c, 0x4fe, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x502, 
    0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x506, 0xa, 0x4c, 0x5, 0x4c, 
    0x508, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x50c, 0xa, 0x4c, 
    0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x510, 0xa, 0x4c, 0x5, 0x4c, 0x512, 
    0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x5, 0x4c, 0x516, 0xa, 0x4c, 0x3, 0x4c, 
    0x3, 0x4c, 0x5, 0x4c, 0x51a, 0xa, 0x4c, 0x3, 0x4c, 0x3, 0x4c, 0x3, 0x4d, 
    0x3, 0x4d, 0x5, 0x4d, 0x520, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 
    0x524, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x528, 0xa, 0x4d, 
    0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x52e, 0xa, 0x4d, 
    0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x532, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 
    0x5, 0x4d, 0x536, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 
    0x5, 0x4d, 0x53c, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x540, 
    0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x544, 0xa, 0x4d, 0x3, 0x4d, 
    0x3, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x54a, 0xa, 0x4d, 0x3, 0x4d, 
    0x3, 0x4d, 0x5, 0x4d, 0x54e, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 
    0x552, 0xa, 0x4d, 0x3, 0x4d, 0x3, 0x4d, 0x5, 0x4d, 0x556, 0xa, 0x4d, 
    0x3, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 0x55a, 0xa, 0x4e, 0x3, 0x4e, 0x5, 0x4e, 
    0x55d, 0xa, 0x4e, 0x3, 0x4f, 0x3, 0x4f, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 
    0x563, 0xa, 0x50, 0x3, 0x50, 0x3, 0x50, 0x5, 0x50, 0x567, 0xa, 0x50, 
    0x3, 0x50, 0x3, 0x50, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 0x51, 0x3, 
    0x51, 0x3, 0x51, 0x3, 0x52, 0x3, 0x52, 0x5, 0x52, 0x573, 0xa, 0x52, 
    0x3, 0x52, 0x3, 0x52, 0x5, 0x52, 0x577, 0xa, 0x52, 0x3, 0x52, 0x3, 0x52, 
    0x5, 0x52, 0x57b, 0xa, 0x52, 0x5, 0x52, 0x57d, 0xa, 0x52, 0x3, 0x52, 
    0x3, 0x52, 0x5, 0x52, 0x581, 0xa, 0x52, 0x3, 0x52, 0x3, 0x52, 0x5, 0x52, 
    0x585, 0xa, 0x52, 0x3, 0x52, 0x3, 0x52, 0x5, 0x52, 0x589, 0xa, 0x52, 
    0x7, 0x52, 0x58b, 0xa, 0x52, 0xc, 0x52, 0xe, 0x52, 0x58e, 0xb, 0x52, 
    0x5, 0x52, 0x590, 0xa, 0x52, 0x3, 0x52, 0x3, 0x52, 0x3, 0x53, 0x3, 0x53, 
    0x3, 0x53, 0x3, 0x54, 0x3, 0x54, 0x5, 0x54, 0x599, 0xa, 0x54, 0x3, 0x54, 
    0x3, 0x54, 0x5, 0x54, 0x59d, 0xa, 0x54, 0x3, 0x54, 0x3, 0x54, 0x3, 0x54, 
    0x5, 0x54, 0x5a2, 0xa, 0x54, 0x3, 0x54, 0x5, 0x54, 0x5a5, 0xa, 0x54, 
    0x5, 0x54, 0x5a7, 0xa, 0x54, 0x3, 0x54, 0x5, 0x54, 0x5aa, 0xa, 0x54, 
    0x3, 0x54, 0x3, 0x54, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x5b0, 0xa, 0x55, 
    0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x5b4, 0xa, 0x55, 0x3, 0x55, 0x3, 0x55, 
    0x5, 0x55, 0x5b8, 0xa, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x5bc, 
    0xa, 0x55, 0x3, 0x55, 0x3, 0x55, 0x5, 0x55, 0x5c0, 0xa, 0x55, 0x7, 0x55, 
    0x5c2, 0xa, 0x55, 0xc, 0x55, 0xe, 0x55, 0x5c5, 0xb, 0x55, 0x5, 0x55, 
    0x5c7, 0xa, 0x55, 0x3, 0x55, 0x3, 0x55, 0x3, 0x56, 0x3, 0x56, 0x3, 0x57, 
    0x3, 0x57, 0x3, 0x58, 0x3, 0x58, 0x3, 0x58, 0x3, 0x59, 0x3, 0x59, 0x3, 
    0x59, 0x7, 0x59, 0x5d5, 0xa, 0x59, 0xc, 0x59, 0xe, 0x59, 0x5d8, 0xb, 
    0x59, 0x3, 0x5a, 0x3, 0x5a, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 0x3, 0x5b, 
    0x3, 0x5b, 0x3, 0x5b, 0x5, 0x5b, 0x5e2, 0xa, 0x5b, 0x3, 0x5c, 0x3, 0x5c, 
    0x3, 0x5d, 0x3, 0x5d, 0x5, 0x5d, 0x5e8, 0xa, 0x5d, 0x3, 0x5e, 0x3, 0x5e, 
    0x3, 0x5f, 0x3, 0x5f, 0x3, 0x60, 0x3, 0x60, 0x5, 0x60, 0x5f0, 0xa, 0x60, 
    0x3, 0x60, 0x3, 0x60, 0x5, 0x60, 0x5f4, 0xa, 0x60, 0x3, 0x60, 0x3, 0x60, 
    0x5, 0x60, 0x5f8, 0xa, 0x60, 0x3, 0x60, 0x3, 0x60, 0x5, 0x60, 0x5fc, 
    0xa, 0x60, 0x7, 0x60, 0x5fe, 0xa, 0x60, 0xc, 0x60, 0xe, 0x60, 0x601, 
    0xb, 0x60, 0x5, 0x60, 0x603, 0xa, 0x60, 0x3, 0x60, 0x3, 0x60, 0x3, 0x61, 
    0x3, 0x61, 0x5, 0x61, 0x609, 0xa, 0x61, 0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 
    0x60d, 0xa, 0x61, 0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 0x611, 0xa, 0x61, 
    0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 0x615, 0xa, 0x61, 0x3, 0x61, 0x3, 0x61, 
    0x5, 0x61, 0x619, 0xa, 0x61, 0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 0x61d, 
    0xa, 0x61, 0x3, 0x61, 0x3, 0x61, 0x5, 0x61, 0x621, 0xa, 0x61, 0x3, 0x61, 
    0x3, 0x61, 0x5, 0x61, 0x625, 0xa, 0x61, 0x7, 0x61, 0x627, 0xa, 0x61, 
    0xc, 0x61, 0xe, 0x61, 0x62a, 0xb, 0x61, 0x5, 0x61, 0x62c, 0xa, 0x61, 
    0x3, 0x61, 0x3, 0x61, 0x3, 0x62, 0x3, 0x62, 0x3, 0x63, 0x3, 0x63, 0x3, 
    0x63, 0x5, 0x63, 0x635, 0xa, 0x63, 0x3, 0x64, 0x3, 0x64, 0x5, 0x64, 
    0x639, 0xa, 0x64, 0x3, 0x65, 0x3, 0x65, 0x3, 0x66, 0x3, 0x66, 0x3, 0x67, 
    0x3, 0x67, 0x3, 0x68, 0x3, 0x68, 0x3, 0x69, 0x3, 0x69, 0x3, 0x69, 0x2, 
    0x2, 0x6a, 0x2, 0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 
    0x18, 0x1a, 0x1c, 0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 
    0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e, 0x40, 0x42, 0x44, 0x46, 
    0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e, 
    0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 
    0x78, 0x7a, 0x7c, 0x7e, 0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 
    0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4, 0xa6, 
    0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe, 
    0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0x2, 0xc, 0x3, 
    0x2, 0x46, 0x49, 0x3, 0x2, 0x14, 0x15, 0x3, 0x2, 0x5f, 0x60, 0x3, 0x2, 
    0x61, 0x63, 0x3, 0x2, 0x6b, 0x6c, 0x7, 0x2, 0x30, 0x3c, 0x3f, 0x54, 
    0x56, 0x5a, 0x5e, 0x60, 0x6f, 0x78, 0x7, 0x2, 0x55, 0x55, 0x5b, 0x5d, 
    0x64, 0x64, 0x79, 0x7b, 0x7e, 0x7e, 0x4, 0x2, 0x10, 0x10, 0x1d, 0x20, 
    0x4, 0x2, 0x11, 0x11, 0x21, 0x24, 0x4, 0x2, 0x15, 0x15, 0x25, 0x2f, 
    0x2, 0x725, 0x2, 0xd3, 0x3, 0x2, 0x2, 0x2, 0x4, 0xe1, 0x3, 0x2, 0x2, 
    0x2, 0x6, 0xe5, 0x3, 0x2, 0x2, 0x2, 0x8, 0xe7, 0x3, 0x2, 0x2, 0x2, 0xa, 
    0xfd, 0x3, 0x2, 0x2, 0x2, 0xc, 0x101, 0x3, 0x2, 0x2, 0x2, 0xe, 0x126, 
    0x3, 0x2, 0x2, 0x2, 0x10, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x12, 0x149, 0x3, 
    0x2, 0x2, 0x2, 0x14, 0x14e, 0x3, 0x2, 0x2, 0x2, 0x16, 0x152, 0x3, 0x2, 
    0x2, 0x2, 0x18, 0x15f, 0x3, 0x2, 0x2, 0x2, 0x1a, 0x169, 0x3, 0x2, 0x2, 
    0x2, 0x1c, 0x17f, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x181, 0x3, 0x2, 0x2, 0x2, 
    0x20, 0x187, 0x3, 0x2, 0x2, 0x2, 0x22, 0x1bd, 0x3, 0x2, 0x2, 0x2, 0x24, 
    0x1c1, 0x3, 0x2, 0x2, 0x2, 0x26, 0x1d5, 0x3, 0x2, 0x2, 0x2, 0x28, 0x1e9, 
    0x3, 0x2, 0x2, 0x2, 0x2a, 0x1eb, 0x3, 0x2, 0x2, 0x2, 0x2c, 0x1f6, 0x3, 
    0x2, 0x2, 0x2, 0x2e, 0x207, 0x3, 0x2, 0x2, 0x2, 0x30, 0x220, 0x3, 0x2, 
    0x2, 0x2, 0x32, 0x224, 0x3, 0x2, 0x2, 0x2, 0x34, 0x22c, 0x3, 0x2, 0x2, 
    0x2, 0x36, 0x233, 0x3, 0x2, 0x2, 0x2, 0x38, 0x25f, 0x3, 0x2, 0x2, 0x2, 
    0x3a, 0x268, 0x3, 0x2, 0x2, 0x2, 0x3c, 0x26a, 0x3, 0x2, 0x2, 0x2, 0x3e, 
    0x279, 0x3, 0x2, 0x2, 0x2, 0x40, 0x27d, 0x3, 0x2, 0x2, 0x2, 0x42, 0x281, 
    0x3, 0x2, 0x2, 0x2, 0x44, 0x288, 0x3, 0x2, 0x2, 0x2, 0x46, 0x28c, 0x3, 
    0x2, 0x2, 0x2, 0x48, 0x2a5, 0x3, 0x2, 0x2, 0x2, 0x4a, 0x2a9, 0x3, 0x2, 
    0x2, 0x2, 0x4c, 0x2ab, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x2cb, 0x3, 0x2, 0x2, 
    0x2, 0x50, 0x2cd, 0x3, 0x2, 0x2, 0x2, 0x52, 0x2d6, 0x3, 0x2, 0x2, 0x2, 
    0x54, 0x2ee, 0x3, 0x2, 0x2, 0x2, 0x56, 0x334, 0x3, 0x2, 0x2, 0x2, 0x58, 
    0x336, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x353, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x355, 
    0x3, 0x2, 0x2, 0x2, 0x5e, 0x36a, 0x3, 0x2, 0x2, 0x2, 0x60, 0x374, 0x3, 
    0x2, 0x2, 0x2, 0x62, 0x37a, 0x3, 0x2, 0x2, 0x2, 0x64, 0x390, 0x3, 0x2, 
    0x2, 0x2, 0x66, 0x392, 0x3, 0x2, 0x2, 0x2, 0x68, 0x394, 0x3, 0x2, 0x2, 
    0x2, 0x6a, 0x39d, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x39f, 0x3, 0x2, 0x2, 0x2, 
    0x6e, 0x3a9, 0x3, 0x2, 0x2, 0x2, 0x70, 0x3b3, 0x3, 0x2, 0x2, 0x2, 0x72, 
    0x3c3, 0x3, 0x2, 0x2, 0x2, 0x74, 0x3c8, 0x3, 0x2, 0x2, 0x2, 0x76, 0x3f0, 
    0x3, 0x2, 0x2, 0x2, 0x78, 0x3f2, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x405, 0x3, 
    0x2, 0x2, 0x2, 0x7c, 0x40c, 0x3, 0x2, 0x2, 0x2, 0x7e, 0x41d, 0x3, 0x2, 
    0x2, 0x2, 0x80, 0x41f, 0x3, 0x2, 0x2, 0x2, 0x82, 0x435, 0x3, 0x2, 0x2, 
    0x2, 0x84, 0x453, 0x3, 0x2, 0x2, 0x2, 0x86, 0x467, 0x3, 0x2, 0x2, 0x2, 
    0x88, 0x469, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x482, 0x3, 0x2, 0x2, 0x2, 0x8c, 
    0x492, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x4b0, 0x3, 0x2, 0x2, 0x2, 0x90, 0x4c8, 
    0x3, 0x2, 0x2, 0x2, 0x92, 0x4d9, 0x3, 0x2, 0x2, 0x2, 0x94, 0x4e7, 0x3, 
    0x2, 0x2, 0x2, 0x96, 0x4fb, 0x3, 0x2, 0x2, 0x2, 0x98, 0x555, 0x3, 0x2, 
    0x2, 0x2, 0x9a, 0x557, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x55e, 0x3, 0x2, 0x2, 
    0x2, 0x9e, 0x560, 0x3, 0x2, 0x2, 0x2, 0xa0, 0x56a, 0x3, 0x2, 0x2, 0x2, 
    0xa2, 0x570, 0x3, 0x2, 0x2, 0x2, 0xa4, 0x593, 0x3, 0x2, 0x2, 0x2, 0xa6, 
    0x596, 0x3, 0x2, 0x2, 0x2, 0xa8, 0x5ad, 0x3, 0x2, 0x2, 0x2, 0xaa, 0x5ca, 
    0x3, 0x2, 0x2, 0x2, 0xac, 0x5cc, 0x3, 0x2, 0x2, 0x2, 0xae, 0x5ce, 0x3, 
    0x2, 0x2, 0x2, 0xb0, 0x5d6, 0x3, 0x2, 0x2, 0x2, 0xb2, 0x5d9, 0x3, 0x2, 
    0x2, 0x2, 0xb4, 0x5e1, 0x3, 0x2, 0x2, 0x2, 0xb6, 0x5e3, 0x3, 0x2, 0x2, 
    0x2, 0xb8, 0x5e7, 0x3, 0x2, 0x2, 0x2, 0xba, 0x5e9, 0x3, 0x2, 0x2, 0x2, 
    0xbc, 0x5eb, 0x3, 0x2, 0x2, 0x2, 0xbe, 0x5ed, 0x3, 0x2, 0x2, 0x2, 0xc0, 
    0x606, 0x3, 0x2, 0x2, 0x2, 0xc2, 0x62f, 0x3, 0x2, 0x2, 0x2, 0xc4, 0x631, 
    0x3, 0x2, 0x2, 0x2, 0xc6, 0x638, 0x3, 0x2, 0x2, 0x2, 0xc8, 0x63a, 0x3, 
    0x2, 0x2, 0x2, 0xca, 0x63c, 0x3, 0x2, 0x2, 0x2, 0xcc, 0x63e, 0x3, 0x2, 
    0x2, 0x2, 0xce, 0x640, 0x3, 0x2, 0x2, 0x2, 0xd0, 0x642, 0x3, 0x2, 0x2, 
    0x2, 0xd2, 0xd4, 0x7, 0x7f, 0x2, 0x2, 0xd3, 0xd2, 0x3, 0x2, 0x2, 0x2, 
    0xd3, 0xd4, 0x3, 0x2, 0x2, 0x2, 0xd4, 0xd5, 0x3, 0x2, 0x2, 0x2, 0xd5, 
    0xda, 0x5, 0x4, 0x3, 0x2, 0xd6, 0xd8, 0x7, 0x7f, 0x2, 0x2, 0xd7, 0xd6, 
    0x3, 0x2, 0x2, 0x2, 0xd7, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd9, 0x3, 
    0x2, 0x2, 0x2, 0xd9, 0xdb, 0x7, 0x3, 0x2, 0x2, 0xda, 0xd7, 0x3, 0x2, 
    0x2, 0x2, 0xda, 0xdb, 0x3, 0x2, 0x2, 0x2, 0xdb, 0xdd, 0x3, 0x2, 0x2, 
    0x2, 0xdc, 0xde, 0x7, 0x7f, 0x2, 0x2, 0xdd, 0xdc, 0x3, 0x2, 0x2, 0x2, 
    0xdd, 0xde, 0x3, 0x2, 0x2, 0x2, 0xde, 0xdf, 0x3, 0x2, 0x2, 0x2, 0xdf, 
    0xe0, 0x7, 0x2, 0x2, 0x3, 0xe0, 0x3, 0x3, 0x2, 0x2, 0x2, 0xe1, 0xe2, 
    0x5, 0x6, 0x4, 0x2, 0xe2, 0x5, 0x3, 0x2, 0x2, 0x2, 0xe3, 0xe6, 0x5, 
    0x8, 0x5, 0x2, 0xe4, 0xe6, 0x5, 0x2c, 0x17, 0x2, 0xe5, 0xe3, 0x3, 0x2, 
    0x2, 0x2, 0xe5, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe6, 0x7, 0x3, 0x2, 0x2, 
    0x2, 0xe7, 0xee, 0x5, 0xc, 0x7, 0x2, 0xe8, 0xea, 0x7, 0x7f, 0x2, 0x2, 
    0xe9, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x3, 0x2, 0x2, 0x2, 0xea, 
    0xeb, 0x3, 0x2, 0x2, 0x2, 0xeb, 0xed, 0x5, 0xa, 0x6, 0x2, 0xec, 0xe9, 
    0x3, 0x2, 0x2, 0x2, 0xed, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xee, 0xec, 0x3, 
    0x2, 0x2, 0x2, 0xee, 0xef, 0x3, 0x2, 0x2, 0x2, 0xef, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0xf0, 0xee, 0x3, 0x2, 0x2, 0x2, 0xf1, 0xf2, 0x7, 0x30, 0x2, 
    0x2, 0xf2, 0xf3, 0x7, 0x7f, 0x2, 0x2, 0xf3, 0xf5, 0x7, 0x31, 0x2, 0x2, 
    0xf4, 0xf6, 0x7, 0x7f, 0x2, 0x2, 0xf5, 0xf4, 0x3, 0x2, 0x2, 0x2, 0xf5, 
    0xf6, 0x3, 0x2, 0x2, 0x2, 0xf6, 0xf7, 0x3, 0x2, 0x2, 0x2, 0xf7, 0xfe, 
    0x5, 0xc, 0x7, 0x2, 0xf8, 0xfa, 0x7, 0x30, 0x2, 0x2, 0xf9, 0xfb, 0x7, 
    0x7f, 0x2, 0x2, 0xfa, 0xf9, 0x3, 0x2, 0x2, 0x2, 0xfa, 0xfb, 0x3, 0x2, 
    0x2, 0x2, 0xfb, 0xfc, 0x3, 0x2, 0x2, 0x2, 0xfc, 0xfe, 0x5, 0xc, 0x7, 
    0x2, 0xfd, 0xf1, 0x3, 0x2, 0x2, 0x2, 0xfd, 0xf8, 0x3, 0x2, 0x2, 0x2, 
    0xfe, 0xb, 0x3, 0x2, 0x2, 0x2, 0xff, 0x102, 0x5, 0xe, 0x8, 0x2, 0x100, 
    0x102, 0x5, 0x10, 0x9, 0x2, 0x101, 0xff, 0x3, 0x2, 0x2, 0x2, 0x101, 
    0x100, 0x3, 0x2, 0x2, 0x2, 0x102, 0xd, 0x3, 0x2, 0x2, 0x2, 0x103, 0x105, 
    0x5, 0x14, 0xb, 0x2, 0x104, 0x106, 0x7, 0x7f, 0x2, 0x2, 0x105, 0x104, 
    0x3, 0x2, 0x2, 0x2, 0x105, 0x106, 0x3, 0x2, 0x2, 0x2, 0x106, 0x108, 
    0x3, 0x2, 0x2, 0x2, 0x107, 0x103, 0x3, 0x2, 0x2, 0x2, 0x108, 0x10b, 
    0x3, 0x2, 0x2, 0x2, 0x109, 0x107, 0x3, 0x2, 0x2, 0x2, 0x109, 0x10a, 
    0x3, 0x2, 0x2, 0x2, 0x10a, 0x10c, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x109, 
    0x3, 0x2, 0x2, 0x2, 0x10c, 0x127, 0x5, 0x34, 0x1b, 0x2, 0x10d, 0x10f, 
    0x5, 0x14, 0xb, 0x2, 0x10e, 0x110, 0x7, 0x7f, 0x2, 0x2, 0x10f, 0x10e, 
    0x3, 0x2, 0x2, 0x2, 0x10f, 0x110, 0x3, 0x2, 0x2, 0x2, 0x110, 0x112, 
    0x3, 0x2, 0x2, 0x2, 0x111, 0x10d, 0x3, 0x2, 0x2, 0x2, 0x112, 0x115, 
    0x3, 0x2, 0x2, 0x2, 0x113, 0x111, 0x3, 0x2, 0x2, 0x2, 0x113, 0x114, 
    0x3, 0x2, 0x2, 0x2, 0x114, 0x116, 0x3, 0x2, 0x2, 0x2, 0x115, 0x113, 
    0x3, 0x2, 0x2, 0x2, 0x116, 0x11d, 0x5, 0x12, 0xa, 0x2, 0x117, 0x119, 
    0x7, 0x7f, 0x2, 0x2, 0x118, 0x117, 0x3, 0x2, 0x2, 0x2, 0x118, 0x119, 
    0x3, 0x2, 0x2, 0x2, 0x119, 0x11a, 0x3, 0x2, 0x2, 0x2, 0x11a, 0x11c, 
    0x5, 0x12, 0xa, 0x2, 0x11b, 0x118, 0x3, 0x2, 0x2, 0x2, 0x11c, 0x11f, 
    0x3, 0x2, 0x2, 0x2, 0x11d, 0x11b, 0x3, 0x2, 0x2, 0x2, 0x11d, 0x11e, 
    0x3, 0x2, 0x2, 0x2, 0x11e, 0x124, 0x3, 0x2, 0x2, 0x2, 0x11f, 0x11d, 
    0x3, 0x2, 0x2, 0x2, 0x120, 0x122, 0x7, 0x7f, 0x2, 0x2, 0x121, 0x120, 
    0x3, 0x2, 0x2, 0x2, 0x121, 0x122, 0x3, 0x2, 0x2, 0x2, 0x122, 0x123, 
    0x3, 0x2, 0x2, 0x2, 0x123, 0x125, 0x5, 0x34, 0x1b, 0x2, 0x124, 0x121, 
    0x3, 0x2, 0x2, 0x2, 0x124, 0x125, 0x3, 0x2, 0x2, 0x2, 0x125, 0x127, 
    0x3, 0x2, 0x2, 0x2, 0x126, 0x109, 0x3, 0x2, 0x2, 0x2, 0x126, 0x113, 
    0x3, 0x2, 0x2, 0x2, 0x127, 0xf, 0x3, 0x2, 0x2, 0x2, 0x128, 0x12a, 0x5, 
    0x14, 0xb, 0x2, 0x129, 0x12b, 0x7, 0x7f, 0x2, 0x2, 0x12a, 0x129, 0x3, 
    0x2, 0x2, 0x2, 0x12a, 0x12b, 0x3, 0x2, 0x2, 0x2, 0x12b, 0x12d, 0x3, 
    0x2, 0x2, 0x2, 0x12c, 0x128, 0x3, 0x2, 0x2, 0x2, 0x12d, 0x130, 0x3, 
    0x2, 0x2, 0x2, 0x12e, 0x12c, 0x3, 0x2, 0x2, 0x2, 0x12e, 0x12f, 0x3, 
    0x2, 0x2, 0x2, 0x12f, 0x137, 0x3, 0x2, 0x2, 0x2, 0x130, 0x12e, 0x3, 
    0x2, 0x2, 0x2, 0x131, 0x133, 0x5, 0x12, 0xa, 0x2, 0x132, 0x134, 0x7, 
    0x7f, 0x2, 0x2, 0x133, 0x132, 0x3, 0x2, 0x2, 0x2, 0x133, 0x134, 0x3, 
    0x2, 0x2, 0x2, 0x134, 0x136, 0x3, 0x2, 0x2, 0x2, 0x135, 0x131, 0x3, 
    0x2, 0x2, 0x2, 0x136, 0x139, 0x3, 0x2, 0x2, 0x2, 0x137, 0x135, 0x3, 
    0x2, 0x2, 0x2, 0x137, 0x138, 0x3, 0x2, 0x2, 0x2, 0x138, 0x13a, 0x3, 
    0x2, 0x2, 0x2, 0x139, 0x137, 0x3, 0x2, 0x2, 0x2, 0x13a, 0x13c, 0x5, 
    0x32, 0x1a, 0x2, 0x13b, 0x13d, 0x7, 0x7f, 0x2, 0x2, 0x13c, 0x13b, 0x3, 
    0x2, 0x2, 0x2, 0x13c, 0x13d, 0x3, 0x2, 0x2, 0x2, 0x13d, 0x13f, 0x3, 
    0x2, 0x2, 0x2, 0x13e, 0x12e, 0x3, 0x2, 0x2, 0x2, 0x13f, 0x140, 0x3, 
    0x2, 0x2, 0x2, 0x140, 0x13e, 0x3, 0x2, 0x2, 0x2, 0x140, 0x141, 0x3, 
    0x2, 0x2, 0x2, 0x141, 0x142, 0x3, 0x2, 0x2, 0x2, 0x142, 0x143, 0x5, 
    0xe, 0x8, 0x2, 0x143, 0x11, 0x3, 0x2, 0x2, 0x2, 0x144, 0x14a, 0x5, 0x1e, 
    0x10, 0x2, 0x145, 0x14a, 0x5, 0x1a, 0xe, 0x2, 0x146, 0x14a, 0x5, 0x24, 
    0x13, 0x2, 0x147, 0x14a, 0x5, 0x20, 0x11, 0x2, 0x148, 0x14a, 0x5, 0x26, 
    0x14, 0x2, 0x149, 0x144, 0x3, 0x2, 0x2, 0x2, 0x149, 0x145, 0x3, 0x2, 
    0x2, 0x2, 0x149, 0x146, 0x3, 0x2, 0x2, 0x2, 0x149, 0x147, 0x3, 0x2, 
    0x2, 0x2, 0x149, 0x148, 0x3, 0x2, 0x2, 0x2, 0x14a, 0x13, 0x3, 0x2, 0x2, 
    0x2, 0x14b, 0x14f, 0x5, 0x16, 0xc, 0x2, 0x14c, 0x14f, 0x5, 0x18, 0xd, 
    0x2, 0x14d, 0x14f, 0x5, 0x2a, 0x16, 0x2, 0x14e, 0x14b, 0x3, 0x2, 0x2, 
    0x2, 0x14e, 0x14c, 0x3, 0x2, 0x2, 0x2, 0x14e, 0x14d, 0x3, 0x2, 0x2, 
    0x2, 0x14f, 0x15, 0x3, 0x2, 0x2, 0x2, 0x150, 0x151, 0x7, 0x32, 0x2, 
    0x2, 0x151, 0x153, 0x7, 0x7f, 0x2, 0x2, 0x152, 0x150, 0x3, 0x2, 0x2, 
    0x2, 0x152, 0x153, 0x3, 0x2, 0x2, 0x2, 0x153, 0x154, 0x3, 0x2, 0x2, 
    0x2, 0x154, 0x156, 0x7, 0x33, 0x2, 0x2, 0x155, 0x157, 0x7, 0x7f, 0x2, 
    0x2, 0x156, 0x155, 0x3, 0x2, 0x2, 0x2, 0x156, 0x157, 0x3, 0x2, 0x2, 
    0x2, 0x157, 0x158, 0x3, 0x2, 0x2, 0x2, 0x158, 0x15d, 0x5, 0x46, 0x24, 
    0x2, 0x159, 0x15b, 0x7, 0x7f, 0x2, 0x2, 0x15a, 0x159, 0x3, 0x2, 0x2, 
    0x2, 0x15a, 0x15b, 0x3, 0x2, 0x2, 0x2, 0x15b, 0x15c, 0x3, 0x2, 0x2, 
    0x2, 0x15c, 0x15e, 0x5, 0x44, 0x23, 0x2, 0x15d, 0x15a, 0x3, 0x2, 0x2, 
    0x2, 0x15d, 0x15e, 0x3, 0x2, 0x2, 0x2, 0x15e, 0x17, 0x3, 0x2, 0x2, 0x2, 
    0x15f, 0x161, 0x7, 0x34, 0x2, 0x2, 0x160, 0x162, 0x7, 0x7f, 0x2, 0x2, 
    0x161, 0x160, 0x3, 0x2, 0x2, 0x2, 0x161, 0x162, 0x3, 0x2, 0x2, 0x2, 
    0x162, 0x163, 0x3, 0x2, 0x2, 0x2, 0x163, 0x164, 0x5, 0x6a, 0x36, 0x2, 
    0x164, 0x165, 0x7, 0x7f, 0x2, 0x2, 0x165, 0x166, 0x7, 0x35, 0x2, 0x2, 
    0x166, 0x167, 0x7, 0x7f, 0x2, 0x2, 0x167, 0x168, 0x5, 0xb2, 0x5a, 0x2, 
    0x168, 0x19, 0x3, 0x2, 0x2, 0x2, 0x169, 0x16b, 0x7, 0x36, 0x2, 0x2, 
    0x16a, 0x16c, 0x7, 0x7f, 0x2, 0x2, 0x16b, 0x16a, 0x3, 0x2, 0x2, 0x2, 
    0x16b, 0x16c, 0x3, 0x2, 0x2, 0x2, 0x16c, 0x16d, 0x3, 0x2, 0x2, 0x2, 
    0x16d, 0x172, 0x5, 0x48, 0x25, 0x2, 0x16e, 0x16f, 0x7, 0x7f, 0x2, 0x2, 
    0x16f, 0x171, 0x5, 0x1c, 0xf, 0x2, 0x170, 0x16e, 0x3, 0x2, 0x2, 0x2, 
    0x171, 0x174, 0x3, 0x2, 0x2, 0x2, 0x172, 0x170, 0x3, 0x2, 0x2, 0x2, 
    0x172, 0x173, 0x3, 0x2, 0x2, 0x2, 0x173, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x174, 
    0x172, 0x3, 0x2, 0x2, 0x2, 0x175, 0x176, 0x7, 0x37, 0x2, 0x2, 0x176, 
    0x177, 0x7, 0x7f, 0x2, 0x2, 0x177, 0x178, 0x7, 0x33, 0x2, 0x2, 0x178, 
    0x179, 0x7, 0x7f, 0x2, 0x2, 0x179, 0x180, 0x5, 0x20, 0x11, 0x2, 0x17a, 
    0x17b, 0x7, 0x37, 0x2, 0x2, 0x17b, 0x17c, 0x7, 0x7f, 0x2, 0x2, 0x17c, 
    0x17d, 0x7, 0x38, 0x2, 0x2, 0x17d, 0x17e, 0x7, 0x7f, 0x2, 0x2, 0x17e, 
    0x180, 0x5, 0x20, 0x11, 0x2, 0x17f, 0x175, 0x3, 0x2, 0x2, 0x2, 0x17f, 
    0x17a, 0x3, 0x2, 0x2, 0x2, 0x180, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x181, 0x183, 
    0x7, 0x38, 0x2, 0x2, 0x182, 0x184, 0x7, 0x7f, 0x2, 0x2, 0x183, 0x182, 
    0x3, 0x2, 0x2, 0x2, 0x183, 0x184, 0x3, 0x2, 0x2, 0x2, 0x184, 0x185, 
    0x3, 0x2, 0x2, 0x2, 0x185, 0x186, 0x5, 0x46, 0x24, 0x2, 0x186, 0x1f, 
    0x3, 0x2, 0x2, 0x2, 0x187, 0x189, 0x7, 0x39, 0x2, 0x2, 0x188, 0x18a, 
    0x7, 0x7f, 0x2, 0x2, 0x189, 0x188, 0x3, 0x2, 0x2, 0x2, 0x189, 0x18a, 
    0x3, 0x2, 0x2, 0x2, 0x18a, 0x18b, 0x3, 0x2, 0x2, 0x2, 0x18b, 0x196, 
    0x5, 0x22, 0x12, 0x2, 0x18c, 0x18e, 0x7, 0x7f, 0x2, 0x2, 0x18d, 0x18c, 
    0x3, 0x2, 0x2, 0x2, 0x18d, 0x18e, 0x3, 0x2, 0x2, 0x2, 0x18e, 0x18f, 
    0x3, 0x2, 0x2, 0x2, 0x18f, 0x191, 0x7, 0x4, 0x2, 0x2, 0x190, 0x192, 
    0x7, 0x7f, 0x2, 0x2, 0x191, 0x190, 0x3, 0x2, 0x2, 0x2, 0x191, 0x192, 
    0x3, 0x2, 0x2, 0x2, 0x192, 0x193, 0x3, 0x2, 0x2, 0x2, 0x193, 0x195, 
    0x5, 0x22, 0x12, 0x2, 0x194, 0x18d, 0x3, 0x2, 0x2, 0x2, 0x195, 0x198, 
    0x3, 0x2, 0x2, 0x2, 0x196, 0x194, 0x3, 0x2, 0x2, 0x2, 0x196, 0x197, 
    0x3, 0x2, 0x2, 0x2, 0x197, 0x21, 0x3, 0x2, 0x2, 0x2, 0x198, 0x196, 0x3, 
    0x2, 0x2, 0x2, 0x199, 0x19b, 0x5, 0x68, 0x35, 0x2, 0x19a, 0x19c, 0x7, 
    0x7f, 0x2, 0x2, 0x19b, 0x19a, 0x3, 0x2, 0x2, 0x2, 0x19b, 0x19c, 0x3, 
    0x2, 0x2, 0x2, 0x19c, 0x19d, 0x3, 0x2, 0x2, 0x2, 0x19d, 0x19f, 0x7, 
    0x5, 0x2, 0x2, 0x19e, 0x1a0, 0x7, 0x7f, 0x2, 0x2, 0x19f, 0x19e, 0x3, 
    0x2, 0x2, 0x2, 0x19f, 0x1a0, 0x3, 0x2, 0x2, 0x2, 0x1a0, 0x1a1, 0x3, 
    0x2, 0x2, 0x2, 0x1a1, 0x1a2, 0x5, 0x6a, 0x36, 0x2, 0x1a2, 0x1be, 0x3, 
    0x2, 0x2, 0x2, 0x1a3, 0x1a5, 0x5, 0xb2, 0x5a, 0x2, 0x1a4, 0x1a6, 0x7, 
    0x7f, 0x2, 0x2, 0x1a5, 0x1a4, 0x3, 0x2, 0x2, 0x2, 0x1a5, 0x1a6, 0x3, 
    0x2, 0x2, 0x2, 0x1a6, 0x1a7, 0x3, 0x2, 0x2, 0x2, 0x1a7, 0x1a9, 0x7, 
    0x5, 0x2, 0x2, 0x1a8, 0x1aa, 0x7, 0x7f, 0x2, 0x2, 0x1a9, 0x1a8, 0x3, 
    0x2, 0x2, 0x2, 0x1a9, 0x1aa, 0x3, 0x2, 0x2, 0x2, 0x1aa, 0x1ab, 0x3, 
    0x2, 0x2, 0x2, 0x1ab, 0x1ac, 0x5, 0x6a, 0x36, 0x2, 0x1ac, 0x1be, 0x3, 
    0x2, 0x2, 0x2, 0x1ad, 0x1af, 0x5, 0xb2, 0x5a, 0x2, 0x1ae, 0x1b0, 0x7, 
    0x7f, 0x2, 0x2, 0x1af, 0x1ae, 0x3, 0x2, 0x2, 0x2, 0x1af, 0x1b0, 0x3, 
    0x2, 0x2, 0x2, 0x1b0, 0x1b1, 0x3, 0x2, 0x2, 0x2, 0x1b1, 0x1b3, 0x7, 
    0x6, 0x2, 0x2, 0x1b2, 0x1b4, 0x7, 0x7f, 0x2, 0x2, 0x1b3, 0x1b2, 0x3, 
    0x2, 0x2, 0x2, 0x1b3, 0x1b4, 0x3, 0x2, 0x2, 0x2, 0x1b4, 0x1b5, 0x3, 
    0x2, 0x2, 0x2, 0x1b5, 0x1b6, 0x5, 0x6a, 0x36, 0x2, 0x1b6, 0x1be, 0x3, 
    0x2, 0x2, 0x2, 0x1b7, 0x1b9, 0x5, 0xb2, 0x5a, 0x2, 0x1b8, 0x1ba, 0x7, 
    0x7f, 0x2, 0x2, 0x1b9, 0x1b8, 0x3, 0x2, 0x2, 0x2, 0x1b9, 0x1ba, 0x3, 
    0x2, 0x2, 0x2, 0x1ba, 0x1bb, 0x3, 0x2, 0x2, 0x2, 0x1bb, 0x1bc, 0x5, 
    0x5e, 0x30, 0x2, 0x1bc, 0x1be, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x199, 0x3, 
    0x2, 0x2, 0x2, 0x1bd, 0x1a3, 0x3, 0x2, 0x2, 0x2, 0x1bd, 0x1ad, 0x3, 
    0x2, 0x2, 0x2, 0x1bd, 0x1b7, 0x3, 0x2, 0x2, 0x2, 0x1be, 0x23, 0x3, 0x2, 
    0x2, 0x2, 0x1bf, 0x1c0, 0x7, 0x3a, 0x2, 0x2, 0x1c0, 0x1c2, 0x7, 0x7f, 
    0x2, 0x2, 0x1c1, 0x1bf, 0x3, 0x2, 0x2, 0x2, 0x1c1, 0x1c2, 0x3, 0x2, 
    0x2, 0x2, 0x1c2, 0x1c3, 0x3, 0x2, 0x2, 0x2, 0x1c3, 0x1c5, 0x7, 0x3b, 
    0x2, 0x2, 0x1c4, 0x1c6, 0x7, 0x7f, 0x2, 0x2, 0x1c5, 0x1c4, 0x3, 0x2, 
    0x2, 0x2, 0x1c5, 0x1c6, 0x3, 0x2, 0x2, 0x2, 0x1c6, 0x1c7, 0x3, 0x2, 
    0x2, 0x2, 0x1c7, 0x1d2, 0x5, 0x6a, 0x36, 0x2, 0x1c8, 0x1ca, 0x7, 0x7f, 
    0x2, 0x2, 0x1c9, 0x1c8, 0x3, 0x2, 0x2, 0x2, 0x1c9, 0x1ca, 0x3, 0x2, 
    0x2, 0x2, 0x1ca, 0x1cb, 0x3, 0x2, 0x2, 0x2, 0x1cb, 0x1cd, 0x7, 0x4, 
    0x2, 0x2, 0x1cc, 0x1ce, 0x7, 0x7f, 0x2, 0x2, 0x1cd, 0x1cc, 0x3, 0x2, 
    0x2, 0x2, 0x1cd, 0x1ce, 0x3, 0x2, 0x2, 0x2, 0x1ce, 0x1cf, 0x3, 0x2, 
    0x2, 0x2, 0x1cf, 0x1d1, 0x5, 0x6a, 0x36, 0x2, 0x1d0, 0x1c9, 0x3, 0x2, 
    0x2, 0x2, 0x1d1, 0x1d4, 0x3, 0x2, 0x2, 0x2, 0x1d2, 0x1d0, 0x3, 0x2, 
    0x2, 0x2, 0x1d2, 0x1d3, 0x3, 0x2, 0x2, 0x2, 0x1d3, 0x25, 0x3, 0x2, 0x2, 
    0x2, 0x1d4, 0x1d2, 0x3, 0x2, 0x2, 0x2, 0x1d5, 0x1d6, 0x7, 0x3c, 0x2, 
    0x2, 0x1d6, 0x1d7, 0x7, 0x7f, 0x2, 0x2, 0x1d7, 0x1e2, 0x5, 0x28, 0x15, 
    0x2, 0x1d8, 0x1da, 0x7, 0x7f, 0x2, 0x2, 0x1d9, 0x1d8, 0x3, 0x2, 0x2, 
    0x2, 0x1d9, 0x1da, 0x3, 0x2, 0x2, 0x2, 0x1da, 0x1db, 0x3, 0x2, 0x2, 
    0x2, 0x1db, 0x1dd, 0x7, 0x4, 0x2, 0x2, 0x1dc, 0x1de, 0x7, 0x7f, 0x2, 
    0x2, 0x1dd, 0x1dc, 0x3, 0x2, 0x2, 0x2, 0x1dd, 0x1de, 0x3, 0x2, 0x2, 
    0x2, 0x1de, 0x1df, 0x3, 0x2, 0x2, 0x2, 0x1df, 0x1e1, 0x5, 0x28, 0x15, 
    0x2, 0x1e0, 0x1d9, 0x3, 0x2, 0x2, 0x2, 0x1e1, 0x1e4, 0x3, 0x2, 0x2, 
    0x2, 0x1e2, 0x1e0, 0x3, 0x2, 0x2, 0x2, 0x1e2, 0x1e3, 0x3, 0x2, 0x2, 
    0x2, 0x1e3, 0x27, 0x3, 0x2, 0x2, 0x2, 0x1e4, 0x1e2, 0x3, 0x2, 0x2, 0x2, 
    0x1e5, 0x1e6, 0x5, 0xb2, 0x5a, 0x2, 0x1e6, 0x1e7, 0x5, 0x5e, 0x30, 0x2, 
    0x1e7, 0x1ea, 0x3, 0x2, 0x2, 0x2, 0x1e8, 0x1ea, 0x5, 0x68, 0x35, 0x2, 
    0x1e9, 0x1e5, 0x3, 0x2, 0x2, 0x2, 0x1e9, 0x1e8, 0x3, 0x2, 0x2, 0x2, 
    0x1ea, 0x29, 0x3, 0x2, 0x2, 0x2, 0x1eb, 0x1ec, 0x7, 0x3d, 0x2, 0x2, 
    0x1ec, 0x1ed, 0x7, 0x7f, 0x2, 0x2, 0x1ed, 0x1f4, 0x5, 0xa8, 0x55, 0x2, 
    0x1ee, 0x1f0, 0x7, 0x7f, 0x2, 0x2, 0x1ef, 0x1ee, 0x3, 0x2, 0x2, 0x2, 
    0x1ef, 0x1f0, 0x3, 0x2, 0x2, 0x2, 0x1f0, 0x1f1, 0x3, 0x2, 0x2, 0x2, 
    0x1f1, 0x1f2, 0x7, 0x3e, 0x2, 0x2, 0x1f2, 0x1f3, 0x7, 0x7f, 0x2, 0x2, 
    0x1f3, 0x1f5, 0x5, 0x2e, 0x18, 0x2, 0x1f4, 0x1ef, 0x3, 0x2, 0x2, 0x2, 
    0x1f4, 0x1f5, 0x3, 0x2, 0x2, 0x2, 0x1f5, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x1f6, 
    0x1f7, 0x7, 0x3d, 0x2, 0x2, 0x1f7, 0x1fa, 0x7, 0x7f, 0x2, 0x2, 0x1f8, 
    0x1fb, 0x5, 0xa8, 0x55, 0x2, 0x1f9, 0x1fb, 0x5, 0xaa, 0x56, 0x2, 0x1fa, 
    0x1f8, 0x3, 0x2, 0x2, 0x2, 0x1fa, 0x1f9, 0x3, 0x2, 0x2, 0x2, 0x1fb, 
    0x205, 0x3, 0x2, 0x2, 0x2, 0x1fc, 0x1fe, 0x7, 0x7f, 0x2, 0x2, 0x1fd, 
    0x1fc, 0x3, 0x2, 0x2, 0x2, 0x1fd, 0x1fe, 0x3, 0x2, 0x2, 0x2, 0x1fe, 
    0x1ff, 0x3, 0x2, 0x2, 0x2, 0x1ff, 0x200, 0x7, 0x3e, 0x2, 0x2, 0x200, 
    0x203, 0x7, 0x7f, 0x2, 0x2, 0x201, 0x204, 0x7, 0x7, 0x2, 0x2, 0x202, 
    0x204, 0x5, 0x2e, 0x18, 0x2, 0x203, 0x201, 0x3, 0x2, 0x2, 0x2, 0x203, 
    0x202, 0x3, 0x2, 0x2, 0x2, 0x204, 0x206, 0x3, 0x2, 0x2, 0x2, 0x205, 
    0x1fd, 0x3, 0x2, 0x2, 0x2, 0x205, 0x206, 0x3, 0x2, 0x2, 0x2, 0x206, 
    0x2d, 0x3, 0x2, 0x2, 0x2, 0x207, 0x212, 0x5, 0x30, 0x19, 0x2, 0x208, 
    0x20a, 0x7, 0x7f, 0x2, 0x2, 0x209, 0x208, 0x3, 0x2, 0x2, 0x2, 0x209, 
    0x20a, 0x3, 0x2, 0x2, 0x2, 0x20a, 0x20b, 0x3, 0x2, 0x2, 0x2, 0x20b, 
    0x20d, 0x7, 0x4, 0x2, 0x2, 0x20c, 0x20e, 0x7, 0x7f, 0x2, 0x2, 0x20d, 
    0x20c, 0x3, 0x2, 0x2, 0x2, 0x20d, 0x20e, 0x3, 0x2, 0x2, 0x2, 0x20e, 
    0x20f, 0x3, 0x2, 0x2, 0x2, 0x20f, 0x211, 0x5, 0x30, 0x19, 0x2, 0x210, 
    0x209, 0x3, 0x2, 0x2, 0x2, 0x211, 0x214, 0x3, 0x2, 0x2, 0x2, 0x212, 
    0x210, 0x3, 0x2, 0x2, 0x2, 0x212, 0x213, 0x3, 0x2, 0x2, 0x2, 0x213, 
    0x219, 0x3, 0x2, 0x2, 0x2, 0x214, 0x212, 0x3, 0x2, 0x2, 0x2, 0x215, 
    0x217, 0x7, 0x7f, 0x2, 0x2, 0x216, 0x215, 0x3, 0x2, 0x2, 0x2, 0x216, 
    0x217, 0x3, 0x2, 0x2, 0x2, 0x217, 0x218, 0x3, 0x2, 0x2, 0x2, 0x218, 
    0x21a, 0x5, 0x44, 0x23, 0x2, 0x219, 0x216, 0x3, 0x2, 0x2, 0x2, 0x219, 
    0x21a, 0x3, 0x2, 0x2, 0x2, 0x21a, 0x2f, 0x3, 0x2, 0x2, 0x2, 0x21b, 0x21c, 
    0x5, 0xac, 0x57, 0x2, 0x21c, 0x21d, 0x7, 0x7f, 0x2, 0x2, 0x21d, 0x21e, 
    0x7, 0x35, 0x2, 0x2, 0x21e, 0x21f, 0x7, 0x7f, 0x2, 0x2, 0x21f, 0x221, 
    0x3, 0x2, 0x2, 0x2, 0x220, 0x21b, 0x3, 0x2, 0x2, 0x2, 0x220, 0x221, 
    0x3, 0x2, 0x2, 0x2, 0x221, 0x222, 0x3, 0x2, 0x2, 0x2, 0x222, 0x223, 
    0x5, 0xb2, 0x5a, 0x2, 0x223, 0x31, 0x3, 0x2, 0x2, 0x2, 0x224, 0x225, 
    0x7, 0x3f, 0x2, 0x2, 0x225, 0x22a, 0x5, 0x36, 0x1c, 0x2, 0x226, 0x228, 
    0x7, 0x7f, 0x2, 0x2, 0x227, 0x226, 0x3, 0x2, 0x2, 0x2, 0x227, 0x228, 
    0x3, 0x2, 0x2, 0x2, 0x228, 0x229, 0x3, 0x2, 0x2, 0x2, 0x229, 0x22b, 
    0x5, 0x44, 0x23, 0x2, 0x22a, 0x227, 0x3, 0x2, 0x2, 0x2, 0x22a, 0x22b, 
    0x3, 0x2, 0x2, 0x2, 0x22b, 0x33, 0x3, 0x2, 0x2, 0x2, 0x22c, 0x22d, 0x7, 
    0x40, 0x2, 0x2, 0x22d, 0x22e, 0x5, 0x36, 0x1c, 0x2, 0x22e, 0x35, 0x3, 
    0x2, 0x2, 0x2, 0x22f, 0x231, 0x7, 0x7f, 0x2, 0x2, 0x230, 0x22f, 0x3, 
    0x2, 0x2, 0x2, 0x230, 0x231, 0x3, 0x2, 0x2, 0x2, 0x231, 0x232, 0x3, 
    0x2, 0x2, 0x2, 0x232, 0x234, 0x7, 0x41, 0x2, 0x2, 0x233, 0x230, 0x3, 
    0x2, 0x2, 0x2, 0x233, 0x234, 0x3, 0x2, 0x2, 0x2, 0x234, 0x235, 0x3, 
    0x2, 0x2, 0x2, 0x235, 0x236, 0x7, 0x7f, 0x2, 0x2, 0x236, 0x239, 0x5, 
    0x38, 0x1d, 0x2, 0x237, 0x238, 0x7, 0x7f, 0x2, 0x2, 0x238, 0x23a, 0x5, 
    0x3c, 0x1f, 0x2, 0x239, 0x237, 0x3, 0x2, 0x2, 0x2, 0x239, 0x23a, 0x3, 
    0x2, 0x2, 0x2, 0x23a, 0x23d, 0x3, 0x2, 0x2, 0x2, 0x23b, 0x23c, 0x7, 
    0x7f, 0x2, 0x2, 0x23c, 0x23e, 0x5, 0x3e, 0x20, 0x2, 0x23d, 0x23b, 0x3, 
    0x2, 0x2, 0x2, 0x23d, 0x23e, 0x3, 0x2, 0x2, 0x2, 0x23e, 0x241, 0x3, 
    0x2, 0x2, 0x2, 0x23f, 0x240, 0x7, 0x7f, 0x2, 0x2, 0x240, 0x242, 0x5, 
    0x40, 0x21, 0x2, 0x241, 0x23f, 0x3, 0x2, 0x2, 0x2, 0x241, 0x242, 0x3, 
    0x2, 0x2, 0x2, 0x242, 0x37, 0x3, 0x2, 0x2, 0x2, 0x243, 0x24e, 0x7, 0x7, 
    0x2, 0x2, 0x244, 0x246, 0x7, 0x7f, 0x2, 0x2, 0x245, 0x244, 0x3, 0x2, 
    0x2, 0x2, 0x245, 0x246, 0x3, 0x2, 0x2, 0x2, 0x246, 0x247, 0x3, 0x2, 
    0x2, 0x2, 0x247, 0x249, 0x7, 0x4, 0x2, 0x2, 0x248, 0x24a, 0x7, 0x7f, 
    0x2, 0x2, 0x249, 0x248, 0x3, 0x2, 0x2, 0x2, 0x249, 0x24a, 0x3, 0x2, 
    0x2, 0x2, 0x24a, 0x24b, 0x3, 0x2, 0x2, 0x2, 0x24b, 0x24d, 0x5, 0x3a, 
    0x1e, 0x2, 0x24c, 0x245, 0x3, 0x2, 0x2, 0x2, 0x24d, 0x250, 0x3, 0x2, 
    0x2, 0x2, 0x24e, 0x24c, 0x3, 0x2, 0x2, 0x2, 0x24e, 0x24f, 0x3, 0x2, 
    0x2, 0x2, 0x24f, 0x260, 0x3, 0x2, 0x2, 0x2, 0x250, 0x24e, 0x3, 0x2, 
    0x2, 0x2, 0x251, 0x25c, 0x5, 0x3a, 0x1e, 0x2, 0x252, 0x254, 0x7, 0x7f, 
    0x2, 0x2, 0x253, 0x252, 0x3, 0x2, 0x2, 0x2, 0x253, 0x254, 0x3, 0x2, 
    0x2, 0x2, 0x254, 0x255, 0x3, 0x2, 0x2, 0x2, 0x255, 0x257, 0x7, 0x4, 
    0x2, 0x2, 0x256, 0x258, 0x7, 0x7f, 0x2, 0x2, 0x257, 0x256, 0x3, 0x2, 
    0x2, 0x2, 0x257, 0x258, 0x3, 0x2, 0x2, 0x2, 0x258, 0x259, 0x3, 0x2, 
    0x2, 0x2, 0x259, 0x25b, 0x5, 0x3a, 0x1e, 0x2, 0x25a, 0x253, 0x3, 0x2, 
    0x2, 0x2, 0x25b, 0x25e, 0x3, 0x2, 0x2, 0x2, 0x25c, 0x25a, 0x3, 0x2, 
    0x2, 0x2, 0x25c, 0x25d, 0x3, 0x2, 0x2, 0x2, 0x25d, 0x260, 0x3, 0x2, 
    0x2, 0x2, 0x25e, 0x25c, 0x3, 0x2, 0x2, 0x2, 0x25f, 0x243, 0x3, 0x2, 
    0x2, 0x2, 0x25f, 0x251, 0x3, 0x2, 0x2, 0x2, 0x260, 0x39, 0x3, 0x2, 0x2, 
    0x2, 0x261, 0x262, 0x5, 0x6a, 0x36, 0x2, 0x262, 0x263, 0x7, 0x7f, 0x2, 
    0x2, 0x263, 0x264, 0x7, 0x35, 0x2, 0x2, 0x264, 0x265, 0x7, 0x7f, 0x2, 
    0x2, 0x265, 0x266, 0x5, 0xb2, 0x5a, 0x2, 0x266, 0x269, 0x3, 0x2, 0x2, 
    0x2, 0x267, 0x269, 0x5, 0x6a, 0x36, 0x2, 0x268, 0x261, 0x3, 0x2, 0x2, 
    0x2, 0x268, 0x267, 0x3, 0x2, 0x2, 0x2, 0x269, 0x3b, 0x3, 0x2, 0x2, 0x2, 
    0x26a, 0x26b, 0x7, 0x42, 0x2, 0x2, 0x26b, 0x26c, 0x7, 0x7f, 0x2, 0x2, 
    0x26c, 0x26d, 0x7, 0x43, 0x2, 0x2, 0x26d, 0x26e, 0x7, 0x7f, 0x2, 0x2, 
    0x26e, 0x276, 0x5, 0x42, 0x22, 0x2, 0x26f, 0x271, 0x7, 0x4, 0x2, 0x2, 
    0x270, 0x272, 0x7, 0x7f, 0x2, 0x2, 0x271, 0x270, 0x3, 0x2, 0x2, 0x2, 
    0x271, 0x272, 0x3, 0x2, 0x2, 0x2, 0x272, 0x273, 0x3, 0x2, 0x2, 0x2, 
    0x273, 0x275, 0x5, 0x42, 0x22, 0x2, 0x274, 0x26f, 0x3, 0x2, 0x2, 0x2, 
    0x275, 0x278, 0x3, 0x2, 0x2, 0x2, 0x276, 0x274, 0x3, 0x2, 0x2, 0x2, 
    0x276, 0x277, 0x3, 0x2, 0x2, 0x2, 0x277, 0x3d, 0x3, 0x2, 0x2, 0x2, 0x278, 
    0x276, 0x3, 0x2, 0x2, 0x2, 0x279, 0x27a, 0x7, 0x44, 0x2, 0x2, 0x27a, 
    0x27b, 0x7, 0x7f, 0x2, 0x2, 0x27b, 0x27c, 0x5, 0x6a, 0x36, 0x2, 0x27c, 
    0x3f, 0x3, 0x2, 0x2, 0x2, 0x27d, 0x27e, 0x7, 0x45, 0x2, 0x2, 0x27e, 
    0x27f, 0x7, 0x7f, 0x2, 0x2, 0x27f, 0x280, 0x5, 0x6a, 0x36, 0x2, 0x280, 
    0x41, 0x3, 0x2, 0x2, 0x2, 0x281, 0x286, 0x5, 0x6a, 0x36, 0x2, 0x282, 
    0x284, 0x7, 0x7f, 0x2, 0x2, 0x283, 0x282, 0x3, 0x2, 0x2, 0x2, 0x283, 
    0x284, 0x3, 0x2, 0x2, 0x2, 0x284, 0x285, 0x3, 0x2, 0x2, 0x2, 0x285, 
    0x287, 0x9, 0x2, 0x2, 0x2, 0x286, 0x283, 0x3, 0x2, 0x2, 0x2, 0x286, 
    0x287, 0x3, 0x2, 0x2, 0x2, 0x287, 0x43, 0x3, 0x2, 0x2, 0x2, 0x288, 0x289, 
    0x7, 0x4a, 0x2, 0x2, 0x289, 0x28a, 0x7, 0x7f, 0x2, 0x2, 0x28a, 0x28b, 
    0x5, 0x6a, 0x36, 0x2, 0x28b, 0x45, 0x3, 0x2, 0x2, 0x2, 0x28c, 0x297, 
    0x5, 0x48, 0x25, 0x2, 0x28d, 0x28f, 0x7, 0x7f, 0x2, 0x2, 0x28e, 0x28d, 
    0x3, 0x2, 0x2, 0x2, 0x28e, 0x28f, 0x3, 0x2, 0x2, 0x2, 0x28f, 0x290, 
    0x3, 0x2, 0x2, 0x2, 0x290, 0x292, 0x7, 0x4, 0x2, 0x2, 0x291, 0x293, 
    0x7, 0x7f, 0x2, 0x2, 0x292, 0x291, 0x3, 0x2, 0x2, 0x2, 0x292, 0x293, 
    0x3, 0x2, 0x2, 0x2, 0x293, 0x294, 0x3, 0x2, 0x2, 0x2, 0x294, 0x296, 
    0x5, 0x48, 0x25, 0x2, 0x295, 0x28e, 0x3, 0x2, 0x2, 0x2, 0x296, 0x299, 
    0x3, 0x2, 0x2, 0x2, 0x297, 0x295, 0x3, 0x2, 0x2, 0x2, 0x297, 0x298, 
    0x3, 0x2, 0x2, 0x2, 0x298, 0x47, 0x3, 0x2, 0x2, 0x2, 0x299, 0x297, 0x3, 
    0x2, 0x2, 0x2, 0x29a, 0x29c, 0x5, 0xb2, 0x5a, 0x2, 0x29b, 0x29d, 0x7, 
    0x7f, 0x2, 0x2, 0x29c, 0x29b, 0x3, 0x2, 0x2, 0x2, 0x29c, 0x29d, 0x3, 
    0x2, 0x2, 0x2, 0x29d, 0x29e, 0x3, 0x2, 0x2, 0x2, 0x29e, 0x2a0, 0x7, 
    0x5, 0x2, 0x2, 0x29f, 0x2a1, 0x7, 0x7f, 0x2, 0x2, 0x2a0, 0x29f, 0x3, 
    0x2, 0x2, 0x2, 0x2a0, 0x2a1, 0x3, 0x2, 0x2, 0x2, 0x2a1, 0x2a2, 0x3, 
    0x2, 0x2, 0x2, 0x2a2, 0x2a3, 0x5, 0x4a, 0x26, 0x2, 0x2a3, 0x2a6, 0x3, 
    0x2, 0x2, 0x2, 0x2a4, 0x2a6, 0x5, 0x4a, 0x26, 0x2, 0x2a5, 0x29a, 0x3, 
    0x2, 0x2, 0x2, 0x2a5, 0x2a4, 0x3, 0x2, 0x2, 0x2, 0x2a6, 0x49, 0x3, 0x2, 
    0x2, 0x2, 0x2a7, 0x2aa, 0x5, 0x4c, 0x27, 0x2, 0x2a8, 0x2aa, 0x5, 0x4e, 
    0x28, 0x2, 0x2a9, 0x2a7, 0x3, 0x2, 0x2, 0x2, 0x2a9, 0x2a8, 0x3, 0x2, 
    0x2, 0x2, 0x2aa, 0x4b, 0x3, 0x2, 0x2, 0x2, 0x2ab, 0x2ad, 0x5, 0xca, 
    0x66, 0x2, 0x2ac, 0x2ae, 0x7, 0x7f, 0x2, 0x2, 0x2ad, 0x2ac, 0x3, 0x2, 
    0x2, 0x2, 0x2ad, 0x2ae, 0x3, 0x2, 0x2, 0x2, 0x2ae, 0x2af, 0x3, 0x2, 
    0x2, 0x2, 0x2af, 0x2b1, 0x7, 0x8, 0x2, 0x2, 0x2b0, 0x2b2, 0x7, 0x7f, 
    0x2, 0x2, 0x2b1, 0x2b0, 0x3, 0x2, 0x2, 0x2, 0x2b1, 0x2b2, 0x3, 0x2, 
    0x2, 0x2, 0x2b2, 0x2b3, 0x3, 0x2, 0x2, 0x2, 0x2b3, 0x2b4, 0x5, 0x4e, 
    0x28, 0x2, 0x2b4, 0x2b6, 0x7, 0x9, 0x2, 0x2, 0x2b5, 0x2b7, 0x7, 0x7f, 
    0x2, 0x2, 0x2b6, 0x2b5, 0x3, 0x2, 0x2, 0x2, 0x2b6, 0x2b7, 0x3, 0x2, 
    0x2, 0x2, 0x2b7, 0x4d, 0x3, 0x2, 0x2, 0x2, 0x2b8, 0x2bf, 0x5, 0x52, 
    0x2a, 0x2, 0x2b9, 0x2bb, 0x7, 0x7f, 0x2, 0x2, 0x2ba, 0x2b9, 0x3, 0x2, 
    0x2, 0x2, 0x2ba, 0x2bb, 0x3, 0x2, 0x2, 0x2, 0x2bb, 0x2bc, 0x3, 0x2, 
    0x2, 0x2, 0x2bc, 0x2be, 0x5, 0x54, 0x2b, 0x2, 0x2bd, 0x2ba, 0x3, 0x2, 
    0x2, 0x2, 0x2be, 0x2c1, 0x3, 0x2, 0x2, 0x2, 0x2bf, 0x2bd, 0x3, 0x2, 
    0x2, 0x2, 0x2bf, 0x2c0, 0x3, 0x2, 0x2, 0x2, 0x2c0, 0x2cc, 0x3, 0x2, 
    0x2, 0x2, 0x2c1, 0x2bf, 0x3, 0x2, 0x2, 0x2, 0x2c2, 0x2c4, 0x7, 0x8, 
    0x2, 0x2, 0x2c3, 0x2c5, 0x7, 0x7f, 0x2, 0x2, 0x2c4, 0x2c3, 0x3, 0x2, 
    0x2, 0x2, 0x2c4, 0x2c5, 0x3, 0x2, 0x2, 0x2, 0x2c5, 0x2c6, 0x3, 0x2, 
    0x2, 0x2, 0x2c6, 0x2c7, 0x5, 0x4e, 0x28, 0x2, 0x2c7, 0x2c9, 0x7, 0x9, 
    0x2, 0x2, 0x2c8, 0x2ca, 0x7, 0x7f, 0x2, 0x2, 0x2c9, 0x2c8, 0x3, 0x2, 
    0x2, 0x2, 0x2c9, 0x2ca, 0x3, 0x2, 0x2, 0x2, 0x2ca, 0x2cc, 0x3, 0x2, 
    0x2, 0x2, 0x2cb, 0x2b8, 0x3, 0x2, 0x2, 0x2, 0x2cb, 0x2c2, 0x3, 0x2, 
    0x2, 0x2, 0x2cc, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x2cd, 0x2d2, 0x5, 0x52, 
    0x2a, 0x2, 0x2ce, 0x2d0, 0x7, 0x7f, 0x2, 0x2, 0x2cf, 0x2ce, 0x3, 0x2, 
    0x2, 0x2, 0x2cf, 0x2d0, 0x3, 0x2, 0x2, 0x2, 0x2d0, 0x2d1, 0x3, 0x2, 
    0x2, 0x2, 0x2d1, 0x2d3, 0x5, 0x54, 0x2b, 0x2, 0x2d2, 0x2cf, 0x3, 0x2, 
    0x2, 0x2, 0x2d3, 0x2d4, 0x3, 0x2, 0x2, 0x2, 0x2d4, 0x2d2, 0x3, 0x2, 
    0x2, 0x2, 0x2d4, 0x2d5, 0x3, 0x2, 0x2, 0x2, 0x2d5, 0x51, 0x3, 0x2, 0x2, 
    0x2, 0x2d6, 0x2d8, 0x7, 0x8, 0x2, 0x2, 0x2d7, 0x2d9, 0x7, 0x7f, 0x2, 
    0x2, 0x2d8, 0x2d7, 0x3, 0x2, 0x2, 0x2, 0x2d8, 0x2d9, 0x3, 0x2, 0x2, 
    0x2, 0x2d9, 0x2de, 0x3, 0x2, 0x2, 0x2, 0x2da, 0x2dc, 0x5, 0xb2, 0x5a, 
    0x2, 0x2db, 0x2dd, 0x7, 0x7f, 0x2, 0x2, 0x2dc, 0x2db, 0x3, 0x2, 0x2, 
    0x2, 0x2dc, 0x2dd, 0x3, 0x2, 0x2, 0x2, 0x2dd, 0x2df, 0x3, 0x2, 0x2, 
    0x2, 0x2de, 0x2da, 0x3, 0x2, 0x2, 0x2, 0x2de, 0x2df, 0x3, 0x2, 0x2, 
    0x2, 0x2df, 0x2e4, 0x3, 0x2, 0x2, 0x2, 0x2e0, 0x2e2, 0x5, 0x5e, 0x30, 
    0x2, 0x2e1, 0x2e3, 0x7, 0x7f, 0x2, 0x2, 0x2e2, 0x2e1, 0x3, 0x2, 0x2, 
    0x2, 0x2e2, 0x2e3, 0x3, 0x2, 0x2, 0x2, 0x2e3, 0x2e5, 0x3, 0x2, 0x2, 
    0x2, 0x2e4, 0x2e0, 0x3, 0x2, 0x2, 0x2, 0x2e4, 0x2e5, 0x3, 0x2, 0x2, 
    0x2, 0x2e5, 0x2ea, 0x3, 0x2, 0x2, 0x2, 0x2e6, 0x2e8, 0x5, 0x5a, 0x2e, 
    0x2, 0x2e7, 0x2e9, 0x7, 0x7f, 0x2, 0x2, 0x2e8, 0x2e7, 0x3, 0x2, 0x2, 
    0x2, 0x2e8, 0x2e9, 0x3, 0x2, 0x2, 0x2, 0x2e9, 0x2eb, 0x3, 0x2, 0x2, 
    0x2, 0x2ea, 0x2e6, 0x3, 0x2, 0x2, 0x2, 0x2ea, 0x2eb, 0x3, 0x2, 0x2, 
    0x2, 0x2eb, 0x2ec, 0x3, 0x2, 0x2, 0x2, 0x2ec, 0x2ed, 0x7, 0x9, 0x2, 
    0x2, 0x2ed, 0x53, 0x3, 0x2, 0x2, 0x2, 0x2ee, 0x2f0, 0x5, 0x56, 0x2c, 
    0x2, 0x2ef, 0x2f1, 0x7, 0x7f, 0x2, 0x2, 0x2f0, 0x2ef, 0x3, 0x2, 0x2, 
    0x2, 0x2f0, 0x2f1, 0x3, 0x2, 0x2, 0x2, 0x2f1, 0x2f2, 0x3, 0x2, 0x2, 
    0x2, 0x2f2, 0x2f3, 0x5, 0x52, 0x2a, 0x2, 0x2f3, 0x55, 0x3, 0x2, 0x2, 
    0x2, 0x2f4, 0x2f6, 0x5, 0xcc, 0x67, 0x2, 0x2f5, 0x2f7, 0x7, 0x7f, 0x2, 
    0x2, 0x2f6, 0x2f5, 0x3, 0x2, 0x2, 0x2, 0x2f6, 0x2f7, 0x3, 0x2, 0x2, 
    0x2, 0x2f7, 0x2f8, 0x3, 0x2, 0x2, 0x2, 0x2f8, 0x2fa, 0x5, 0xd0, 0x69, 
    0x2, 0x2f9, 0x2fb, 0x7, 0x7f, 0x2, 0x2, 0x2fa, 0x2f9, 0x3, 0x2, 0x2, 
    0x2, 0x2fa, 0x2fb, 0x3, 0x2, 0x2, 0x2, 0x2fb, 0x2fd, 0x3, 0x2, 0x2, 
    0x2, 0x2fc, 0x2fe, 0x5, 0x58, 0x2d, 0x2, 0x2fd, 0x2fc, 0x3, 0x2, 0x2, 
    0x2, 0x2fd, 0x2fe, 0x3, 0x2, 0x2, 0x2, 0x2fe, 0x300, 0x3, 0x2, 0x2, 
    0x2, 0x2ff, 0x301, 0x7, 0x7f, 0x2, 0x2, 0x300, 0x2ff, 0x3, 0x2, 0x2, 
    0x2, 0x300, 0x301, 0x3, 0x2, 0x2, 0x2, 0x301, 0x302, 0x3, 0x2, 0x2, 
    0x2, 0x302, 0x304, 0x5, 0xd0, 0x69, 0x2, 0x303, 0x305, 0x7, 0x7f, 0x2, 
    0x2, 0x304, 0x303, 0x3, 0x2, 0x2, 0x2, 0x304, 0x305, 0x3, 0x2, 0x2, 
    0x2, 0x305, 0x306, 0x3, 0x2, 0x2, 0x2, 0x306, 0x307, 0x5, 0xce, 0x68, 
    0x2, 0x307, 0x335, 0x3, 0x2, 0x2, 0x2, 0x308, 0x30a, 0x5, 0xcc, 0x67, 
    0x2, 0x309, 0x30b, 0x7, 0x7f, 0x2, 0x2, 0x30a, 0x309, 0x3, 0x2, 0x2, 
    0x2, 0x30a, 0x30b, 0x3, 0x2, 0x2, 0x2, 0x30b, 0x30c, 0x3, 0x2, 0x2, 
    0x2, 0x30c, 0x30e, 0x5, 0xd0, 0x69, 0x2, 0x30d, 0x30f, 0x7, 0x7f, 0x2, 
    0x2, 0x30e, 0x30d, 0x3, 0x2, 0x2, 0x2, 0x30e, 0x30f, 0x3, 0x2, 0x2, 
    0x2, 0x30f, 0x311, 0x3, 0x2, 0x2, 0x2, 0x310, 0x312, 0x5, 0x58, 0x2d, 
    0x2, 0x311, 0x310, 0x3, 0x2, 0x2, 0x2, 0x311, 0x312, 0x3, 0x2, 0x2, 
    0x2, 0x312, 0x314, 0x3, 0x2, 0x2, 0x2, 0x313, 0x315, 0x7, 0x7f, 0x2, 
    0x2, 0x314, 0x313, 0x3, 0x2, 0x2, 0x2, 0x314, 0x315, 0x3, 0x2, 0x2, 
    0x2, 0x315, 0x316, 0x3, 0x2, 0x2, 0x2, 0x316, 0x317, 0x5, 0xd0, 0x69, 
    0x2, 0x317, 0x335, 0x3, 0x2, 0x2, 0x2, 0x318, 0x31a, 0x5, 0xd0, 0x69, 
    0x2, 0x319, 0x31b, 0x7, 0x7f, 0x2, 0x2, 0x31a, 0x319, 0x3, 0x2, 0x2, 
    0x2, 0x31a, 0x31b, 0x3, 0x2, 0x2, 0x2, 0x31b, 0x31d, 0x3, 0x2, 0x2, 
    0x2, 0x31c, 0x31e, 0x5, 0x58, 0x2d, 0x2, 0x31d, 0x31c, 0x3, 0x2, 0x2, 
    0x2, 0x31d, 0x31e, 0x3, 0x2, 0x2, 0x2, 0x31e, 0x320, 0x3, 0x2, 0x2, 
    0x2, 0x31f, 0x321, 0x7, 0x7f, 0x2, 0x2, 0x320, 0x31f, 0x3, 0x2, 0x2, 
    0x2, 0x320, 0x321, 0x3, 0x2, 0x2, 0x2, 0x321, 0x322, 0x3, 0x2, 0x2, 
    0x2, 0x322, 0x324, 0x5, 0xd0, 0x69, 0x2, 0x323, 0x325, 0x7, 0x7f, 0x2, 
    0x2, 0x324, 0x323, 0x3, 0x2, 0x2, 0x2, 0x324, 0x325, 0x3, 0x2, 0x2, 
    0x2, 0x325, 0x326, 0x3, 0x2, 0x2, 0x2, 0x326, 0x327, 0x5, 0xce, 0x68, 
    0x2, 0x327, 0x335, 0x3, 0x2, 0x2, 0x2, 0x328, 0x32a, 0x5, 0xd0, 0x69, 
    0x2, 0x329, 0x32b, 0x7, 0x7f, 0x2, 0x2, 0x32a, 0x329, 0x3, 0x2, 0x2, 
    0x2, 0x32a, 0x32b, 0x3, 0x2, 0x2, 0x2, 0x32b, 0x32d, 0x3, 0x2, 0x2, 
    0x2, 0x32c, 0x32e, 0x5, 0x58, 0x2d, 0x2, 0x32d, 0x32c, 0x3, 0x2, 0x2, 
    0x2, 0x32d, 0x32e, 0x3, 0x2, 0x2, 0x2, 0x32e, 0x330, 0x3, 0x2, 0x2, 
    0x2, 0x32f, 0x331, 0x7, 0x7f, 0x2, 0x2, 0x330, 0x32f, 0x3, 0x2, 0x2, 
    0x2, 0x330, 0x331, 0x3, 0x2, 0x2, 0x2, 0x331, 0x332, 0x3, 0x2, 0x2, 
    0x2, 0x332, 0x333, 0x5, 0xd0, 0x69, 0x2, 0x333, 0x335, 0x3, 0x2, 0x2, 
    0x2, 0x334, 0x2f4, 0x3, 0x2, 0x2, 0x2, 0x334, 0x308, 0x3, 0x2, 0x2, 
    0x2, 0x334, 0x318, 0x3, 0x2, 0x2, 0x2, 0x334, 0x328, 0x3, 0x2, 0x2, 
    0x2, 0x335, 0x57, 0x3, 0x2, 0x2, 0x2, 0x336, 0x338, 0x7, 0xa, 0x2, 0x2, 
    0x337, 0x339, 0x7, 0x7f, 0x2, 0x2, 0x338, 0x337, 0x3, 0x2, 0x2, 0x2, 
    0x338, 0x339, 0x3, 0x2, 0x2, 0x2, 0x339, 0x33e, 0x3, 0x2, 0x2, 0x2, 
    0x33a, 0x33c, 0x5, 0xb2, 0x5a, 0x2, 0x33b, 0x33d, 0x7, 0x7f, 0x2, 0x2, 
    0x33c, 0x33b, 0x3, 0x2, 0x2, 0x2, 0x33c, 0x33d, 0x3, 0x2, 0x2, 0x2, 
    0x33d, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x33e, 0x33a, 0x3, 0x2, 0x2, 0x2, 
    0x33e, 0x33f, 0x3, 0x2, 0x2, 0x2, 0x33f, 0x344, 0x3, 0x2, 0x2, 0x2, 
    0x340, 0x342, 0x5, 0x5c, 0x2f, 0x2, 0x341, 0x343, 0x7, 0x7f, 0x2, 0x2, 
    0x342, 0x341, 0x3, 0x2, 0x2, 0x2, 0x342, 0x343, 0x3, 0x2, 0x2, 0x2, 
    0x343, 0x345, 0x3, 0x2, 0x2, 0x2, 0x344, 0x340, 0x3, 0x2, 0x2, 0x2, 
    0x344, 0x345, 0x3, 0x2, 0x2, 0x2, 0x345, 0x347, 0x3, 0x2, 0x2, 0x2, 
    0x346, 0x348, 0x5, 0x62, 0x32, 0x2, 0x347, 0x346, 0x3, 0x2, 0x2, 0x2, 
    0x347, 0x348, 0x3, 0x2, 0x2, 0x2, 0x348, 0x34d, 0x3, 0x2, 0x2, 0x2, 
    0x349, 0x34b, 0x5, 0x5a, 0x2e, 0x2, 0x34a, 0x34c, 0x7, 0x7f, 0x2, 0x2, 
    0x34b, 0x34a, 0x3, 0x2, 0x2, 0x2, 0x34b, 0x34c, 0x3, 0x2, 0x2, 0x2, 
    0x34c, 0x34e, 0x3, 0x2, 0x2, 0x2, 0x34d, 0x349, 0x3, 0x2, 0x2, 0x2, 
    0x34d, 0x34e, 0x3, 0x2, 0x2, 0x2, 0x34e, 0x34f, 0x3, 0x2, 0x2, 0x2, 
    0x34f, 0x350, 0x7, 0xb, 0x2, 0x2, 0x350, 0x59, 0x3, 0x2, 0x2, 0x2, 0x351, 
    0x354, 0x5, 0xc0, 0x61, 0x2, 0x352, 0x354, 0x5, 0xc4, 0x63, 0x2, 0x353, 
    0x351, 0x3, 0x2, 0x2, 0x2, 0x353, 0x352, 0x3, 0x2, 0x2, 0x2, 0x354, 
    0x5b, 0x3, 0x2, 0x2, 0x2, 0x355, 0x357, 0x7, 0xc, 0x2, 0x2, 0x356, 0x358, 
    0x7, 0x7f, 0x2, 0x2, 0x357, 0x356, 0x3, 0x2, 0x2, 0x2, 0x357, 0x358, 
    0x3, 0x2, 0x2, 0x2, 0x358, 0x359, 0x3, 0x2, 0x2, 0x2, 0x359, 0x367, 
    0x5, 0x66, 0x34, 0x2, 0x35a, 0x35c, 0x7, 0x7f, 0x2, 0x2, 0x35b, 0x35a, 
    0x3, 0x2, 0x2, 0x2, 0x35b, 0x35c, 0x3, 0x2, 0x2, 0x2, 0x35c, 0x35d, 
    0x3, 0x2, 0x2, 0x2, 0x35d, 0x35f, 0x7, 0xd, 0x2, 0x2, 0x35e, 0x360, 
    0x7, 0xc, 0x2, 0x2, 0x35f, 0x35e, 0x3, 0x2, 0x2, 0x2, 0x35f, 0x360, 
    0x3, 0x2, 0x2, 0x2, 0x360, 0x362, 0x3, 0x2, 0x2, 0x2, 0x361, 0x363, 
    0x7, 0x7f, 0x2, 0x2, 0x362, 0x361, 0x3, 0x2, 0x2, 0x2, 0x362, 0x363, 
    0x3, 0x2, 0x2, 0x2, 0x363, 0x364, 0x3, 0x2, 0x2, 0x2, 0x364, 0x366, 
    0x5, 0x66, 0x34, 0x2, 0x365, 0x35b, 0x3, 0x2, 0x2, 0x2, 0x366, 0x369, 
    0x3, 0x2, 0x2, 0x2, 0x367, 0x365, 0x3, 0x2, 0x2, 0x2, 0x367, 0x368, 
    0x3, 0x2, 0x2, 0x2, 0x368, 0x5d, 0x3, 0x2, 0x2, 0x2, 0x369, 0x367, 0x3, 
    0x2, 0x2, 0x2, 0x36a, 0x371, 0x5, 0x60, 0x31, 0x2, 0x36b, 0x36d, 0x7, 
    0x7f, 0x2, 0x2, 0x36c, 0x36b, 0x3, 0x2, 0x2, 0x2, 0x36c, 0x36d, 0x3, 
    0x2, 0x2, 0x2, 0x36d, 0x36e, 0x3, 0x2, 0x2, 0x2, 0x36e, 0x370, 0x5, 
    0x60, 0x31, 0x2, 0x36f, 0x36c, 0x3, 0x2, 0x2, 0x2, 0x370, 0x373, 0x3, 
    0x2, 0x2, 0x2, 0x371, 0x36f, 0x3, 0x2, 0x2, 0x2, 0x371, 0x372, 0x3, 
    0x2, 0x2, 0x2, 0x372, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x373, 0x371, 0x3, 0x2, 
    0x2, 0x2, 0x374, 0x376, 0x7, 0xc, 0x2, 0x2, 0x375, 0x377, 0x7, 0x7f, 
    0x2, 0x2, 0x376, 0x375, 0x3, 0x2, 0x2, 0x2, 0x376, 0x377, 0x3, 0x2, 
    0x2, 0x2, 0x377, 0x378, 0x3, 0x2, 0x2, 0x2, 0x378, 0x379, 0x5, 0x64, 
    0x33, 0x2, 0x379, 0x61, 0x3, 0x2, 0x2, 0x2, 0x37a, 0x37c, 0x7, 0x7, 
    0x2, 0x2, 0x37b, 0x37d, 0x7, 0x7f, 0x2, 0x2, 0x37c, 0x37b, 0x3, 0x2, 
    0x2, 0x2, 0x37c, 0x37d, 0x3, 0x2, 0x2, 0x2, 0x37d, 0x382, 0x3, 0x2, 
    0x2, 0x2, 0x37e, 0x380, 0x5, 0xba, 0x5e, 0x2, 0x37f, 0x381, 0x7, 0x7f, 
    0x2, 0x2, 0x380, 0x37f, 0x3, 0x2, 0x2, 0x2, 0x380, 0x381, 0x3, 0x2, 
    0x2, 0x2, 0x381, 0x383, 0x3, 0x2, 0x2, 0x2, 0x382, 0x37e, 0x3, 0x2, 
    0x2, 0x2, 0x382, 0x383, 0x3, 0x2, 0x2, 0x2, 0x383, 0x38e, 0x3, 0x2, 
    0x2, 0x2, 0x384, 0x386, 0x7, 0xe, 0x2, 0x2, 0x385, 0x387, 0x7, 0x7f, 
    0x2, 0x2, 0x386, 0x385, 0x3, 0x2, 0x2, 0x2, 0x386, 0x387, 0x3, 0x2, 
    0x2, 0x2, 0x387, 0x38c, 0x3, 0x2, 0x2, 0x2, 0x388, 0x38a, 0x5, 0xba, 
    0x5e, 0x2, 0x389, 0x38b, 0x7, 0x7f, 0x2, 0x2, 0x38a, 0x389, 0x3, 0x2, 
    0x2, 0x2, 0x38a, 0x38b, 0x3, 0x2, 0x2, 0x2, 0x38b, 0x38d, 0x3, 0x2, 
    0x2, 0x2, 0x38c, 0x388, 0x3, 0x2, 0x2, 0x2, 0x38c, 0x38d, 0x3, 0x2, 
    0x2, 0x2, 0x38d, 0x38f, 0x3, 0x2, 0x2, 0x2, 0x38e, 0x384, 0x3, 0x2, 
    0x2, 0x2, 0x38e, 0x38f, 0x3, 0x2, 0x2, 0x2, 0x38f, 0x63, 0x3, 0x2, 0x2, 
    0x2, 0x390, 0x391, 0x5, 0xc6, 0x64, 0x2, 0x391, 0x65, 0x3, 0x2, 0x2, 
    0x2, 0x392, 0x393, 0x5, 0xc6, 0x64, 0x2, 0x393, 0x67, 0x3, 0x2, 0x2, 
    0x2, 0x394, 0x399, 0x5, 0x8e, 0x48, 0x2, 0x395, 0x397, 0x7, 0x7f, 0x2, 
    0x2, 0x396, 0x395, 0x3, 0x2, 0x2, 0x2, 0x396, 0x397, 0x3, 0x2, 0x2, 
    0x2, 0x397, 0x398, 0x3, 0x2, 0x2, 0x2, 0x398, 0x39a, 0x5, 0x8c, 0x47, 
    0x2, 0x399, 0x396, 0x3, 0x2, 0x2, 0x2, 0x39a, 0x39b, 0x3, 0x2, 0x2, 
    0x2, 0x39b, 0x399, 0x3, 0x2, 0x2, 0x2, 0x39b, 0x39c, 0x3, 0x2, 0x2, 
    0x2, 0x39c, 0x69, 0x3, 0x2, 0x2, 0x2, 0x39d, 0x39e, 0x5, 0x6c, 0x37, 
    0x2, 0x39e, 0x6b, 0x3, 0x2, 0x2, 0x2, 0x39f, 0x3a6, 0x5, 0x6e, 0x38, 
    0x2, 0x3a0, 0x3a1, 0x7, 0x7f, 0x2, 0x2, 0x3a1, 0x3a2, 0x7, 0x4b, 0x2, 
    0x2, 0x3a2, 0x3a3, 0x7, 0x7f, 0x2, 0x2, 0x3a3, 0x3a5, 0x5, 0x6e, 0x38, 
    0x2, 0x3a4, 0x3a0, 0x3, 0x2, 0x2, 0x2, 0x3a5, 0x3a8, 0x3, 0x2, 0x2, 
    0x2, 0x3a6, 0x3a4, 0x3, 0x2, 0x2, 0x2, 0x3a6, 0x3a7, 0x3, 0x2, 0x2, 
    0x2, 0x3a7, 0x6d, 0x3, 0x2, 0x2, 0x2, 0x3a8, 0x3a6, 0x3, 0x2, 0x2, 0x2, 
    0x3a9, 0x3b0, 0x5, 0x70, 0x39, 0x2, 0x3aa, 0x3ab, 0x7, 0x7f, 0x2, 0x2, 
    0x3ab, 0x3ac, 0x7, 0x4c, 0x2, 0x2, 0x3ac, 0x3ad, 0x7, 0x7f, 0x2, 0x2, 
    0x3ad, 0x3af, 0x5, 0x70, 0x39, 0x2, 0x3ae, 0x3aa, 0x3, 0x2, 0x2, 0x2, 
    0x3af, 0x3b2, 0x3, 0x2, 0x2, 0x2, 0x3b0, 0x3ae, 0x3, 0x2, 0x2, 0x2, 
    0x3b0, 0x3b1, 0x3, 0x2, 0x2, 0x2, 0x3b1, 0x6f, 0x3, 0x2, 0x2, 0x2, 0x3b2, 
    0x3b0, 0x3, 0x2, 0x2, 0x2, 0x3b3, 0x3ba, 0x5, 0x72, 0x3a, 0x2, 0x3b4, 
    0x3b5, 0x7, 0x7f, 0x2, 0x2, 0x3b5, 0x3b6, 0x7, 0x4d, 0x2, 0x2, 0x3b6, 
    0x3b7, 0x7, 0x7f, 0x2, 0x2, 0x3b7, 0x3b9, 0x5, 0x72, 0x3a, 0x2, 0x3b8, 
    0x3b4, 0x3, 0x2, 0x2, 0x2, 0x3b9, 0x3bc, 0x3, 0x2, 0x2, 0x2, 0x3ba, 
    0x3b8, 0x3, 0x2, 0x2, 0x2, 0x3ba, 0x3bb, 0x3, 0x2, 0x2, 0x2, 0x3bb, 
    0x71, 0x3, 0x2, 0x2, 0x2, 0x3bc, 0x3ba, 0x3, 0x2, 0x2, 0x2, 0x3bd, 0x3bf, 
    0x7, 0x4e, 0x2, 0x2, 0x3be, 0x3c0, 0x7, 0x7f, 0x2, 0x2, 0x3bf, 0x3be, 
    0x3, 0x2, 0x2, 0x2, 0x3bf, 0x3c0, 0x3, 0x2, 0x2, 0x2, 0x3c0, 0x3c2, 
    0x3, 0x2, 0x2, 0x2, 0x3c1, 0x3bd, 0x3, 0x2, 0x2, 0x2, 0x3c2, 0x3c5, 
    0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c1, 0x3, 0x2, 0x2, 0x2, 0x3c3, 0x3c4, 
    0x3, 0x2, 0x2, 0x2, 0x3c4, 0x3c6, 0x3, 0x2, 0x2, 0x2, 0x3c5, 0x3c3, 
    0x3, 0x2, 0x2, 0x2, 0x3c6, 0x3c7, 0x5, 0x74, 0x3b, 0x2, 0x3c7, 0x73, 
    0x3, 0x2, 0x2, 0x2, 0x3c8, 0x3cf, 0x5, 0x78, 0x3d, 0x2, 0x3c9, 0x3cb, 
    0x7, 0x7f, 0x2, 0x2, 0x3ca, 0x3c9, 0x3, 0x2, 0x2, 0x2, 0x3ca, 0x3cb, 
    0x3, 0x2, 0x2, 0x2, 0x3cb, 0x3cc, 0x3, 0x2, 0x2, 0x2, 0x3cc, 0x3ce, 
    0x5, 0x76, 0x3c, 0x2, 0x3cd, 0x3ca, 0x3, 0x2, 0x2, 0x2, 0x3ce, 0x3d1, 
    0x3, 0x2, 0x2, 0x2, 0x3cf, 0x3cd, 0x3, 0x2, 0x2, 0x2, 0x3cf, 0x3d0, 
    0x3, 0x2, 0x2, 0x2, 0x3d0, 0x75, 0x3, 0x2, 0x2, 0x2, 0x3d1, 0x3cf, 0x3, 
    0x2, 0x2, 0x2, 0x3d2, 0x3d4, 0x7, 0x5, 0x2, 0x2, 0x3d3, 0x3d5, 0x7, 
    0x7f, 0x2, 0x2, 0x3d4, 0x3d3, 0x3, 0x2, 0x2, 0x2, 0x3d4, 0x3d5, 0x3, 
    0x2, 0x2, 0x2, 0x3d5, 0x3d6, 0x3, 0x2, 0x2, 0x2, 0x3d6, 0x3f1, 0x5, 
    0x78, 0x3d, 0x2, 0x3d7, 0x3d9, 0x7, 0xf, 0x2, 0x2, 0x3d8, 0x3da, 0x7, 
    0x7f, 0x2, 0x2, 0x3d9, 0x3d8, 0x3, 0x2, 0x2, 0x2, 0x3d9, 0x3da, 0x3, 
    0x2, 0x2, 0x2, 0x3da, 0x3db, 0x3, 0x2, 0x2, 0x2, 0x3db, 0x3f1, 0x5, 
    0x78, 0x3d, 0x2, 0x3dc, 0x3de, 0x7, 0x10, 0x2, 0x2, 0x3dd, 0x3df, 0x7, 
    0x7f, 0x2, 0x2, 0x3de, 0x3dd, 0x3, 0x2, 0x2, 0x2, 0x3de, 0x3df, 0x3, 
    0x2, 0x2, 0x2, 0x3df, 0x3e0, 0x3, 0x2, 0x2, 0x2, 0x3e0, 0x3f1, 0x5, 
    0x78, 0x3d, 0x2, 0x3e1, 0x3e3, 0x7, 0x11, 0x2, 0x2, 0x3e2, 0x3e4, 0x7, 
    0x7f, 0x2, 0x2, 0x3e3, 0x3e2, 0x3, 0x2, 0x2, 0x2, 0x3e3, 0x3e4, 0x3, 
    0x2, 0x2, 0x2, 0x3e4, 0x3e5, 0x3, 0x2, 0x2, 0x2, 0x3e5, 0x3f1, 0x5, 
    0x78, 0x3d, 0x2, 0x3e6, 0x3e8, 0x7, 0x12, 0x2, 0x2, 0x3e7, 0x3e9, 0x7, 
    0x7f, 0x2, 0x2, 0x3e8, 0x3e7, 0x3, 0x2, 0x2, 0x2, 0x3e8, 0x3e9, 0x3, 
    0x2, 0x2, 0x2, 0x3e9, 0x3ea, 0x3, 0x2, 0x2, 0x2, 0x3ea, 0x3f1, 0x5, 
    0x78, 0x3d, 0x2, 0x3eb, 0x3ed, 0x7, 0x13, 0x2, 0x2, 0x3ec, 0x3ee, 0x7, 
    0x7f, 0x2, 0x2, 0x3ed, 0x3ec, 0x3, 0x2, 0x2, 0x2, 0x3ed, 0x3ee, 0x3, 
    0x2, 0x2, 0x2, 0x3ee, 0x3ef, 0x3, 0x2, 0x2, 0x2, 0x3ef, 0x3f1, 0x5, 
    0x78, 0x3d, 0x2, 0x3f0, 0x3d2, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3d7, 0x3, 
    0x2, 0x2, 0x2, 0x3f0, 0x3dc, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3e1, 0x3, 
    0x2, 0x2, 0x2, 0x3f0, 0x3e6, 0x3, 0x2, 0x2, 0x2, 0x3f0, 0x3eb, 0x3, 
    0x2, 0x2, 0x2, 0x3f1, 0x77, 0x3, 0x2, 0x2, 0x2, 0x3f2, 0x3f8, 0x5, 0x80, 
    0x41, 0x2, 0x3f3, 0x3f7, 0x5, 0x7a, 0x3e, 0x2, 0x3f4, 0x3f7, 0x5, 0x7c, 
    0x3f, 0x2, 0x3f5, 0x3f7, 0x5, 0x7e, 0x40, 0x2, 0x3f6, 0x3f3, 0x3, 0x2, 
    0x2, 0x2, 0x3f6, 0x3f4, 0x3, 0x2, 0x2, 0x2, 0x3f6, 0x3f5, 0x3, 0x2, 
    0x2, 0x2, 0x3f7, 0x3fa, 0x3, 0x2, 0x2, 0x2, 0x3f8, 0x3f6, 0x3, 0x2, 
    0x2, 0x2, 0x3f8, 0x3f9, 0x3, 0x2, 0x2, 0x2, 0x3f9, 0x79, 0x3, 0x2, 0x2, 
    0x2, 0x3fa, 0x3f8, 0x3, 0x2, 0x2, 0x2, 0x3fb, 0x3fc, 0x7, 0x7f, 0x2, 
    0x2, 0x3fc, 0x3fd, 0x7, 0x4f, 0x2, 0x2, 0x3fd, 0x3fe, 0x7, 0x7f, 0x2, 
    0x2, 0x3fe, 0x406, 0x7, 0x3f, 0x2, 0x2, 0x3ff, 0x400, 0x7, 0x7f, 0x2, 
    0x2, 0x400, 0x401, 0x7, 0x50, 0x2, 0x2, 0x401, 0x402, 0x7, 0x7f, 0x2, 
    0x2, 0x402, 0x406, 0x7, 0x3f, 0x2, 0x2, 0x403, 0x404, 0x7, 0x7f, 0x2, 
    0x2, 0x404, 0x406, 0x7, 0x51, 0x2, 0x2, 0x405, 0x3fb, 0x3, 0x2, 0x2, 
    0x2, 0x405, 0x3ff, 0x3, 0x2, 0x2, 0x2, 0x405, 0x403, 0x3, 0x2, 0x2, 
    0x2, 0x406, 0x408, 0x3, 0x2, 0x2, 0x2, 0x407, 0x409, 0x7, 0x7f, 0x2, 
    0x2, 0x408, 0x407, 0x3, 0x2, 0x2, 0x2, 0x408, 0x409, 0x3, 0x2, 0x2, 
    0x2, 0x409, 0x40a, 0x3, 0x2, 0x2, 0x2, 0x40a, 0x40b, 0x5, 0x80, 0x41, 
    0x2, 0x40b, 0x7b, 0x3, 0x2, 0x2, 0x2, 0x40c, 0x40d, 0x7, 0x7f, 0x2, 
    0x2, 0x40d, 0x40f, 0x7, 0x52, 0x2, 0x2, 0x40e, 0x410, 0x7, 0x7f, 0x2, 
    0x2, 0x40f, 0x40e, 0x3, 0x2, 0x2, 0x2, 0x40f, 0x410, 0x3, 0x2, 0x2, 
    0x2, 0x410, 0x411, 0x3, 0x2, 0x2, 0x2, 0x411, 0x412, 0x5, 0x80, 0x41, 
    0x2, 0x412, 0x7d, 0x3, 0x2, 0x2, 0x2, 0x413, 0x414, 0x7, 0x7f, 0x2, 
    0x2, 0x414, 0x415, 0x7, 0x53, 0x2, 0x2, 0x415, 0x416, 0x7, 0x7f, 0x2, 
    0x2, 0x416, 0x41e, 0x7, 0x54, 0x2, 0x2, 0x417, 0x418, 0x7, 0x7f, 0x2, 
    0x2, 0x418, 0x419, 0x7, 0x53, 0x2, 0x2, 0x419, 0x41a, 0x7, 0x7f, 0x2, 
    0x2, 0x41a, 0x41b, 0x7, 0x4e, 0x2, 0x2, 0x41b, 0x41c, 0x7, 0x7f, 0x2, 
    0x2, 0x41c, 0x41e, 0x7, 0x54, 0x2, 0x2, 0x41d, 0x413, 0x3, 0x2, 0x2, 
    0x2, 0x41d, 0x417, 0x3, 0x2, 0x2, 0x2, 0x41e, 0x7f, 0x3, 0x2, 0x2, 0x2, 
    0x41f, 0x432, 0x5, 0x82, 0x42, 0x2, 0x420, 0x422, 0x7, 0x7f, 0x2, 0x2, 
    0x421, 0x420, 0x3, 0x2, 0x2, 0x2, 0x421, 0x422, 0x3, 0x2, 0x2, 0x2, 
    0x422, 0x423, 0x3, 0x2, 0x2, 0x2, 0x423, 0x425, 0x7, 0x14, 0x2, 0x2, 
    0x424, 0x426, 0x7, 0x7f, 0x2, 0x2, 0x425, 0x424, 0x3, 0x2, 0x2, 0x2, 
    0x425, 0x426, 0x3, 0x2, 0x2, 0x2, 0x426, 0x427, 0x3, 0x2, 0x2, 0x2, 
    0x427, 0x431, 0x5, 0x82, 0x42, 0x2, 0x428, 0x42a, 0x7, 0x7f, 0x2, 0x2, 
    0x429, 0x428, 0x3, 0x2, 0x2, 0x2, 0x429, 0x42a, 0x3, 0x2, 0x2, 0x2, 
    0x42a, 0x42b, 0x3, 0x2, 0x2, 0x2, 0x42b, 0x42d, 0x7, 0x15, 0x2, 0x2, 
    0x42c, 0x42e, 0x7, 0x7f, 0x2, 0x2, 0x42d, 0x42c, 0x3, 0x2, 0x2, 0x2, 
    0x42d, 0x42e, 0x3, 0x2, 0x2, 0x2, 0x42e, 0x42f, 0x3, 0x2, 0x2, 0x2, 
    0x42f, 0x431, 0x5, 0x82, 0x42, 0x2, 0x430, 0x421, 0x3, 0x2, 0x2, 0x2, 
    0x430, 0x429, 0x3, 0x2, 0x2, 0x2, 0x431, 0x434, 0x3, 0x2, 0x2, 0x2, 
    0x432, 0x430, 0x3, 0x2, 0x2, 0x2, 0x432, 0x433, 0x3, 0x2, 0x2, 0x2, 
    0x433, 0x81, 0x3, 0x2, 0x2, 0x2, 0x434, 0x432, 0x3, 0x2, 0x2, 0x2, 0x435, 
    0x450, 0x5, 0x84, 0x43, 0x2, 0x436, 0x438, 0x7, 0x7f, 0x2, 0x2, 0x437, 
    0x436, 0x3, 0x2, 0x2, 0x2, 0x437, 0x438, 0x3, 0x2, 0x2, 0x2, 0x438, 
    0x439, 0x3, 0x2, 0x2, 0x2, 0x439, 0x43b, 0x7, 0x7, 0x2, 0x2, 0x43a, 
    0x43c, 0x7, 0x7f, 0x2, 0x2, 0x43b, 0x43a, 0x3, 0x2, 0x2, 0x2, 0x43b, 
    0x43c, 0x3, 0x2, 0x2, 0x2, 0x43c, 0x43d, 0x3, 0x2, 0x2, 0x2, 0x43d, 
    0x44f, 0x5, 0x84, 0x43, 0x2, 0x43e, 0x440, 0x7, 0x7f, 0x2, 0x2, 0x43f, 
    0x43e, 0x3, 0x2, 0x2, 0x2, 0x43f, 0x440, 0x3, 0x2, 0x2, 0x2, 0x440, 
    0x441, 0x3, 0x2, 0x2, 0x2, 0x441, 0x443, 0x7, 0x16, 0x2, 0x2, 0x442, 
    0x444, 0x7, 0x7f, 0x2, 0x2, 0x443, 0x442, 0x3, 0x2, 0x2, 0x2, 0x443, 
    0x444, 0x3, 0x2, 0x2, 0x2, 0x444, 0x445, 0x3, 0x2, 0x2, 0x2, 0x445, 
    0x44f, 0x5, 0x84, 0x43, 0x2, 0x446, 0x448, 0x7, 0x7f, 0x2, 0x2, 0x447, 
    0x446, 0x3, 0x2, 0x2, 0x2, 0x447, 0x448, 0x3, 0x2, 0x2, 0x2, 0x448, 
    0x449, 0x3, 0x2, 0x2, 0x2, 0x449, 0x44b, 0x7, 0x17, 0x2, 0x2, 0x44a, 
    0x44c, 0x7, 0x7f, 0x2, 0x2, 0x44b, 0x44a, 0x3, 0x2, 0x2, 0x2, 0x44b, 
    0x44c, 0x3, 0x2, 0x2, 0x2, 0x44c, 0x44d, 0x3, 0x2, 0x2, 0x2, 0x44d, 
    0x44f, 0x5, 0x84, 0x43, 0x2, 0x44e, 0x437, 0x3, 0x2, 0x2, 0x2, 0x44e, 
    0x43f, 0x3, 0x2, 0x2, 0x2, 0x44e, 0x447, 0x3, 0x2, 0x2, 0x2, 0x44f, 
    0x452, 0x3, 0x2, 0x2, 0x2, 0x450, 0x44e, 0x3, 0x2, 0x2, 0x2, 0x450, 
    0x451, 0x3, 0x2, 0x2, 0x2, 0x451, 0x83, 0x3, 0x2, 0x2, 0x2, 0x452, 0x450, 
    0x3, 0x2, 0x2, 0x2, 0x453, 0x45e, 0x5, 0x86, 0x44, 0x2, 0x454, 0x456, 
    0x7, 0x7f, 0x2, 0x2, 0x455, 0x454, 0x3, 0x2, 0x2, 0x2, 0x455, 0x456, 
    0x3, 0x2, 0x2, 0x2, 0x456, 0x457, 0x3, 0x2, 0x2, 0x2, 0x457, 0x459, 
    0x7, 0x18, 0x2, 0x2, 0x458, 0x45a, 0x7, 0x7f, 0x2, 0x2, 0x459, 0x458, 
    0x3, 0x2, 0x2, 0x2, 0x459, 0x45a, 0x3, 0x2, 0x2, 0x2, 0x45a, 0x45b, 
    0x3, 0x2, 0x2, 0x2, 0x45b, 0x45d, 0x5, 0x86, 0x44, 0x2, 0x45c, 0x455, 
    0x3, 0x2, 0x2, 0x2, 0x45d, 0x460, 0x3, 0x2, 0x2, 0x2, 0x45e, 0x45c, 
    0x3, 0x2, 0x2, 0x2, 0x45e, 0x45f, 0x3, 0x2, 0x2, 0x2, 0x45f, 0x85, 0x3, 
    0x2, 0x2, 0x2, 0x460, 0x45e, 0x3, 0x2, 0x2, 0x2, 0x461, 0x468, 0x5, 
    0x88, 0x45, 0x2, 0x462, 0x464, 0x9, 0x3, 0x2, 0x2, 0x463, 0x465, 0x7, 
    0x7f, 0x2, 0x2, 0x464, 0x463, 0x3, 0x2, 0x2, 0x2, 0x464, 0x465, 0x3, 
    0x2, 0x2, 0x2, 0x465, 0x466, 0x3, 0x2, 0x2, 0x2, 0x466, 0x468, 0x5, 
    0x88, 0x45, 0x2, 0x467, 0x461, 0x3, 0x2, 0x2, 0x2, 0x467, 0x462, 0x3, 
    0x2, 0x2, 0x2, 0x468, 0x87, 0x3, 0x2, 0x2, 0x2, 0x469, 0x47f, 0x5, 0x8a, 
    0x46, 0x2, 0x46a, 0x46c, 0x7, 0x7f, 0x2, 0x2, 0x46b, 0x46a, 0x3, 0x2, 
    0x2, 0x2, 0x46b, 0x46c, 0x3, 0x2, 0x2, 0x2, 0x46c, 0x46d, 0x3, 0x2, 
    0x2, 0x2, 0x46d, 0x46e, 0x7, 0xa, 0x2, 0x2, 0x46e, 0x46f, 0x5, 0x6a, 
    0x36, 0x2, 0x46f, 0x470, 0x7, 0xb, 0x2, 0x2, 0x470, 0x47e, 0x3, 0x2, 
    0x2, 0x2, 0x471, 0x473, 0x7, 0x7f, 0x2, 0x2, 0x472, 0x471, 0x3, 0x2, 
    0x2, 0x2, 0x472, 0x473, 0x3, 0x2, 0x2, 0x2, 0x473, 0x474, 0x3, 0x2, 
    0x2, 0x2, 0x474, 0x476, 0x7, 0xa, 0x2, 0x2, 0x475, 0x477, 0x5, 0x6a, 
    0x36, 0x2, 0x476, 0x475, 0x3, 0x2, 0x2, 0x2, 0x476, 0x477, 0x3, 0x2, 
    0x2, 0x2, 0x477, 0x478, 0x3, 0x2, 0x2, 0x2, 0x478, 0x47a, 0x7, 0xe, 
    0x2, 0x2, 0x479, 0x47b, 0x5, 0x6a, 0x36, 0x2, 0x47a, 0x479, 0x3, 0x2, 
    0x2, 0x2, 0x47a, 0x47b, 0x3, 0x2, 0x2, 0x2, 0x47b, 0x47c, 0x3, 0x2, 
    0x2, 0x2, 0x47c, 0x47e, 0x7, 0xb, 0x2, 0x2, 0x47d, 0x46b, 0x3, 0x2, 
    0x2, 0x2, 0x47d, 0x472, 0x3, 0x2, 0x2, 0x2, 0x47e, 0x481, 0x3, 0x2, 
    0x2, 0x2, 0x47f, 0x47d, 0x3, 0x2, 0x2, 0x2, 0x47f, 0x480, 0x3, 0x2, 
    0x2, 0x2, 0x480, 0x89, 0x3, 0x2, 0x2, 0x2, 0x481, 0x47f, 0x3, 0x2, 0x2, 
    0x2, 0x482, 0x489, 0x5, 0x8e, 0x48, 0x2, 0x483, 0x485, 0x7, 0x7f, 0x2, 
    0x2, 0x484, 0x483, 0x3, 0x2, 0x2, 0x2, 0x484, 0x485, 0x3, 0x2, 0x2, 
    0x2, 0x485, 0x486, 0x3, 0x2, 0x2, 0x2, 0x486, 0x488, 0x5, 0x8c, 0x47, 
    0x2, 0x487, 0x484, 0x3, 0x2, 0x2, 0x2, 0x488, 0x48b, 0x3, 0x2, 0x2, 
    0x2, 0x489, 0x487, 0x3, 0x2, 0x2, 0x2, 0x489, 0x48a, 0x3, 0x2, 0x2, 
    0x2, 0x48a, 0x490, 0x3, 0x2, 0x2, 0x2, 0x48b, 0x489, 0x3, 0x2, 0x2, 
    0x2, 0x48c, 0x48e, 0x7, 0x7f, 0x2, 0x2, 0x48d, 0x48c, 0x3, 0x2, 0x2, 
    0x2, 0x48d, 0x48e, 0x3, 0x2, 0x2, 0x2, 0x48e, 0x48f, 0x3, 0x2, 0x2, 
    0x2, 0x48f, 0x491, 0x5, 0x5e, 0x30, 0x2, 0x490, 0x48d, 0x3, 0x2, 0x2, 
    0x2, 0x490, 0x491, 0x3, 0x2, 0x2, 0x2, 0x491, 0x8b, 0x3, 0x2, 0x2, 0x2, 
    0x492, 0x494, 0x7, 0x19, 0x2, 0x2, 0x493, 0x495, 0x7, 0x7f, 0x2, 0x2, 
    0x494, 0x493, 0x3, 0x2, 0x2, 0x2, 0x494, 0x495, 0x3, 0x2, 0x2, 0x2, 
    0x495, 0x496, 0x3, 0x2, 0x2, 0x2, 0x496, 0x497, 0x5, 0xc2, 0x62, 0x2, 
    0x497, 0x8d, 0x3, 0x2, 0x2, 0x2, 0x498, 0x4b1, 0x5, 0xb4, 0x5b, 0x2, 
    0x499, 0x4b1, 0x5, 0xc4, 0x63, 0x2, 0x49a, 0x4b1, 0x5, 0x90, 0x49, 0x2, 
    0x49b, 0x49d, 0x7, 0x55, 0x2, 0x2, 0x49c, 0x49e, 0x7, 0x7f, 0x2, 0x2, 
    0x49d, 0x49c, 0x3, 0x2, 0x2, 0x2, 0x49d, 0x49e, 0x3, 0x2, 0x2, 0x2, 
    0x49e, 0x49f, 0x3, 0x2, 0x2, 0x2, 0x49f, 0x4a1, 0x7, 0x8, 0x2, 0x2, 
    0x4a0, 0x4a2, 0x7, 0x7f, 0x2, 0x2, 0x4a1, 0x4a0, 0x3, 0x2, 0x2, 0x2, 
    0x4a1, 0x4a2, 0x3, 0x2, 0x2, 0x2, 0x4a2, 0x4a3, 0x3, 0x2, 0x2, 0x2, 
    0x4a3, 0x4a5, 0x7, 0x7, 0x2, 0x2, 0x4a4, 0x4a6, 0x7, 0x7f, 0x2, 0x2, 
    0x4a5, 0x4a4, 0x3, 0x2, 0x2, 0x2, 0x4a5, 0x4a6, 0x3, 0x2, 0x2, 0x2, 
    0x4a6, 0x4a7, 0x3, 0x2, 0x2, 0x2, 0x4a7, 0x4b1, 0x7, 0x9, 0x2, 0x2, 
    0x4a8, 0x4b1, 0x5, 0x94, 0x4b, 0x2, 0x4a9, 0x4b1, 0x5, 0x96, 0x4c, 0x2, 
    0x4aa, 0x4b1, 0x5, 0x98, 0x4d, 0x2, 0x4ab, 0x4b1, 0x5, 0x9c, 0x4f, 0x2, 
    0x4ac, 0x4b1, 0x5, 0x9e, 0x50, 0x2, 0x4ad, 0x4b1, 0x5, 0xa2, 0x52, 0x2, 
    0x4ae, 0x4b1, 0x5, 0xa6, 0x54, 0x2, 0x4af, 0x4b1, 0x5, 0xb2, 0x5a, 0x2, 
    0x4b0, 0x498, 0x3, 0x2, 0x2, 0x2, 0x4b0, 0x499, 0x3, 0x2, 0x2, 0x2, 
    0x4b0, 0x49a, 0x3, 0x2, 0x2, 0x2, 0x4b0, 0x49b, 0x3, 0x2, 0x2, 0x2, 
    0x4b0, 0x4a8, 0x3, 0x2, 0x2, 0x2, 0x4b0, 0x4a9, 0x3, 0x2, 0x2, 0x2, 
    0x4b0, 0x4aa, 0x3, 0x2, 0x2, 0x2, 0x4b0, 0x4ab, 0x3, 0x2, 0x2, 0x2, 
    0x4b0, 0x4ac, 0x3, 0x2, 0x2, 0x2, 0x4b0, 0x4ad, 0x3, 0x2, 0x2, 0x2, 
    0x4b0, 0x4ae, 0x3, 0x2, 0x2, 0x2, 0x4b0, 0x4af, 0x3, 0x2, 0x2, 0x2, 
    0x4b1, 0x8f, 0x3, 0x2, 0x2, 0x2, 0x4b2, 0x4b7, 0x7, 0x56, 0x2, 0x2, 
    0x4b3, 0x4b5, 0x7, 0x7f, 0x2, 0x2, 0x4b4, 0x4b3, 0x3, 0x2, 0x2, 0x2, 
    0x4b4, 0x4b5, 0x3, 0x2, 0x2, 0x2, 0x4b5, 0x4b6, 0x3, 0x2, 0x2, 0x2, 
    0x4b6, 0x4b8, 0x5, 0x92, 0x4a, 0x2, 0x4b7, 0x4b4, 0x3, 0x2, 0x2, 0x2, 
    0x4b8, 0x4b9, 0x3, 0x2, 0x2, 0x2, 0x4b9, 0x4b7, 0x3, 0x2, 0x2, 0x2, 
    0x4b9, 0x4ba, 0x3, 0x2, 0x2, 0x2, 0x4ba, 0x4c9, 0x3, 0x2, 0x2, 0x2, 
    0x4bb, 0x4bd, 0x7, 0x56, 0x2, 0x2, 0x4bc, 0x4be, 0x7, 0x7f, 0x2, 0x2, 
    0x4bd, 0x4bc, 0x3, 0x2, 0x2, 0x2, 0x4bd, 0x4be, 0x3, 0x2, 0x2, 0x2, 
    0x4be, 0x4bf, 0x3, 0x2, 0x2, 0x2, 0x4bf, 0x4c4, 0x5, 0x6a, 0x36, 0x2, 
    0x4c0, 0x4c2, 0x7, 0x7f, 0x2, 0x2, 0x4c1, 0x4c0, 0x3, 0x2, 0x2, 0x2, 
    0x4c1, 0x4c2, 0x3, 0x2, 0x2, 0x2, 0x4c2, 0x4c3, 0x3, 0x2, 0x2, 0x2, 
    0x4c3, 0x4c5, 0x5, 0x92, 0x4a, 0x2, 0x4c4, 0x4c1, 0x3, 0x2, 0x2, 0x2, 
    0x4c5, 0x4c6, 0x3, 0x2, 0x2, 0x2, 0x4c6, 0x4c4, 0x3, 0x2, 0x2, 0x2, 
    0x4c6, 0x4c7, 0x3, 0x2, 0x2, 0x2, 0x4c7, 0x4c9, 0x3, 0x2, 0x2, 0x2, 
    0x4c8, 0x4b2, 0x3, 0x2, 0x2, 0x2, 0x4c8, 0x4bb, 0x3, 0x2, 0x2, 0x2, 
    0x4c9, 0x4d2, 0x3, 0x2, 0x2, 0x2, 0x4ca, 0x4cc, 0x7, 0x7f, 0x2, 0x2, 
    0x4cb, 0x4ca, 0x3, 0x2, 0x2, 0x2, 0x4cb, 0x4cc, 0x3, 0x2, 0x2, 0x2, 
    0x4cc, 0x4cd, 0x3, 0x2, 0x2, 0x2, 0x4cd, 0x4cf, 0x7, 0x57, 0x2, 0x2, 
    0x4ce, 0x4d0, 0x7, 0x7f, 0x2, 0x2, 0x4cf, 0x4ce, 0x3, 0x2, 0x2, 0x2, 
    0x4cf, 0x4d0, 0x3, 0x2, 0x2, 0x2, 0x4d0, 0x4d1, 0x3, 0x2, 0x2, 0x2, 
    0x4d1, 0x4d3, 0x5, 0x6a, 0x36, 0x2, 0x4d2, 0x4cb, 0x3, 0x2, 0x2, 0x2, 
    0x4d2, 0x4d3, 0x3, 0x2, 0x2, 0x2, 0x4d3, 0x4d5, 0x3, 0x2, 0x2, 0x2, 
    0x4d4, 0x4d6, 0x7, 0x7f, 0x2, 0x2, 0x4d5, 0x4d4, 0x3, 0x2, 0x2, 0x2, 
    0x4d5, 0x4d6, 0x3, 0x2, 0x2, 0x2, 0x4d6, 0x4d7, 0x3, 0x2, 0x2, 0x2, 
    0x4d7, 0x4d8, 0x7, 0x58, 0x2, 0x2, 0x4d8, 0x91, 0x3, 0x2, 0x2, 0x2, 
    0x4d9, 0x4db, 0x7, 0x59, 0x2, 0x2, 0x4da, 0x4dc, 0x7, 0x7f, 0x2, 0x2, 
    0x4db, 0x4da, 0x3, 0x2, 0x2, 0x2, 0x4db, 0x4dc, 0x3, 0x2, 0x2, 0x2, 
    0x4dc, 0x4dd, 0x3, 0x2, 0x2, 0x2, 0x4dd, 0x4df, 0x5, 0x6a, 0x36, 0x2, 
    0x4de, 0x4e0, 0x7, 0x7f, 0x2, 0x2, 0x4df, 0x4de, 0x3, 0x2, 0x2, 0x2, 
    0x4df, 0x4e0, 0x3, 0x2, 0x2, 0x2, 0x4e0, 0x4e1, 0x3, 0x2, 0x2, 0x2, 
    0x4e1, 0x4e3, 0x7, 0x5a, 0x2, 0x2, 0x4e2, 0x4e4, 0x7, 0x7f, 0x2, 0x2, 
    0x4e3, 0x4e2, 0x3, 0x2, 0x2, 0x2, 0x4e3, 0x4e4, 0x3, 0x2, 0x2, 0x2, 
    0x4e4, 0x4e5, 0x3, 0x2, 0x2, 0x2, 0x4e5, 0x4e6, 0x5, 0x6a, 0x36, 0x2, 
    0x4e6, 0x93, 0x3, 0x2, 0x2, 0x2, 0x4e7, 0x4e9, 0x7, 0xa, 0x2, 0x2, 0x4e8, 
    0x4ea, 0x7, 0x7f, 0x2, 0x2, 0x4e9, 0x4e8, 0x3, 0x2, 0x2, 0x2, 0x4e9, 
    0x4ea, 0x3, 0x2, 0x2, 0x2, 0x4ea, 0x4eb, 0x3, 0x2, 0x2, 0x2, 0x4eb, 
    0x4f4, 0x5, 0x9a, 0x4e, 0x2, 0x4ec, 0x4ee, 0x7, 0x7f, 0x2, 0x2, 0x4ed, 
    0x4ec, 0x3, 0x2, 0x2, 0x2, 0x4ed, 0x4ee, 0x3, 0x2, 0x2, 0x2, 0x4ee, 
    0x4ef, 0x3, 0x2, 0x2, 0x2, 0x4ef, 0x4f1, 0x7, 0xd, 0x2, 0x2, 0x4f0, 
    0x4f2, 0x7, 0x7f, 0x2, 0x2, 0x4f1, 0x4f0, 0x3, 0x2, 0x2, 0x2, 0x4f1, 
    0x4f2, 0x3, 0x2, 0x2, 0x2, 0x4f2, 0x4f3, 0x3, 0x2, 0x2, 0x2, 0x4f3, 
    0x4f5, 0x5, 0x6a, 0x36, 0x2, 0x4f4, 0x4ed, 0x3, 0x2, 0x2, 0x2, 0x4f4, 
    0x4f5, 0x3, 0x2, 0x2, 0x2, 0x4f5, 0x4f7, 0x3, 0x2, 0x2, 0x2, 0x4f6, 
    0x4f8, 0x7, 0x7f, 0x2, 0x2, 0x4f7, 0x4f6, 0x3, 0x2, 0x2, 0x2, 0x4f7, 
    0x4f8, 0x3, 0x2, 0x2, 0x2, 0x4f8, 0x4f9, 0x3, 0x2, 0x2, 0x2, 0x4f9, 
    0x4fa, 0x7, 0xb, 0x2, 0x2, 0x4fa, 0x95, 0x3, 0x2, 0x2, 0x2, 0x4fb, 0x4fd, 
    0x7, 0xa, 0x2, 0x2, 0x4fc, 0x4fe, 0x7, 0x7f, 0x2, 0x2, 0x4fd, 0x4fc, 
    0x3, 0x2, 0x2, 0x2, 0x4fd, 0x4fe, 0x3, 0x2, 0x2, 0x2, 0x4fe, 0x507, 
    0x3, 0x2, 0x2, 0x2, 0x4ff, 0x501, 0x5, 0xb2, 0x5a, 0x2, 0x500, 0x502, 
    0x7, 0x7f, 0x2, 0x2, 0x501, 0x500, 0x3, 0x2, 0x2, 0x2, 0x501, 0x502, 
    0x3, 0x2, 0x2, 0x2, 0x502, 0x503, 0x3, 0x2, 0x2, 0x2, 0x503, 0x505, 
    0x7, 0x5, 0x2, 0x2, 0x504, 0x506, 0x7, 0x7f, 0x2, 0x2, 0x505, 0x504, 
    0x3, 0x2, 0x2, 0x2, 0x505, 0x506, 0x3, 0x2, 0x2, 0x2, 0x506, 0x508, 
    0x3, 0x2, 0x2, 0x2, 0x507, 0x4ff, 0x3, 0x2, 0x2, 0x2, 0x507, 0x508, 
    0x3, 0x2, 0x2, 0x2, 0x508, 0x509, 0x3, 0x2, 0x2, 0x2, 0x509, 0x50b, 
    0x5, 0x50, 0x29, 0x2, 0x50a, 0x50c, 0x7, 0x7f, 0x2, 0x2, 0x50b, 0x50a, 
    0x3, 0x2, 0x2, 0x2, 0x50b, 0x50c, 0x3, 0x2, 0x2, 0x2, 0x50c, 0x511, 
    0x3, 0x2, 0x2, 0x2, 0x50d, 0x50f, 0x5, 0x44, 0x23, 0x2, 0x50e, 0x510, 
    0x7, 0x7f, 0x2, 0x2, 0x50f, 0x50e, 0x3, 0x2, 0x2, 0x2, 0x50f, 0x510, 
    0x3, 0x2, 0x2, 0x2, 0x510, 0x512, 0x3, 0x2, 0x2, 0x2, 0x511, 0x50d, 
    0x3, 0x2, 0x2, 0x2, 0x511, 0x512, 0x3, 0x2, 0x2, 0x2, 0x512, 0x513, 
    0x3, 0x2, 0x2, 0x2, 0x513, 0x515, 0x7, 0xd, 0x2, 0x2, 0x514, 0x516, 
    0x7, 0x7f, 0x2, 0x2, 0x515, 0x514, 0x3, 0x2, 0x2, 0x2, 0x515, 0x516, 
    0x3, 0x2, 0x2, 0x2, 0x516, 0x517, 0x3, 0x2, 0x2, 0x2, 0x517, 0x519, 
    0x5, 0x6a, 0x36, 0x2, 0x518, 0x51a, 0x7, 0x7f, 0x2, 0x2, 0x519, 0x518, 
    0x3, 0x2, 0x2, 0x2, 0x519, 0x51a, 0x3, 0x2, 0x2, 0x2, 0x51a, 0x51b, 
    0x3, 0x2, 0x2, 0x2, 0x51b, 0x51c, 0x7, 0xb, 0x2, 0x2, 0x51c, 0x97, 0x3, 
    0x2, 0x2, 0x2, 0x51d, 0x51f, 0x7, 0x31, 0x2, 0x2, 0x51e, 0x520, 0x7, 
    0x7f, 0x2, 0x2, 0x51f, 0x51e, 0x3, 0x2, 0x2, 0x2, 0x51f, 0x520, 0x3, 
    0x2, 0x2, 0x2, 0x520, 0x521, 0x3, 0x2, 0x2, 0x2, 0x521, 0x523, 0x7, 
    0x8, 0x2, 0x2, 0x522, 0x524, 0x7, 0x7f, 0x2, 0x2, 0x523, 0x522, 0x3, 
    0x2, 0x2, 0x2, 0x523, 0x524, 0x3, 0x2, 0x2, 0x2, 0x524, 0x525, 0x3, 
    0x2, 0x2, 0x2, 0x525, 0x527, 0x5, 0x9a, 0x4e, 0x2, 0x526, 0x528, 0x7, 
    0x7f, 0x2, 0x2, 0x527, 0x526, 0x3, 0x2, 0x2, 0x2, 0x527, 0x528, 0x3, 
    0x2, 0x2, 0x2, 0x528, 0x529, 0x3, 0x2, 0x2, 0x2, 0x529, 0x52a, 0x7, 
    0x9, 0x2, 0x2, 0x52a, 0x556, 0x3, 0x2, 0x2, 0x2, 0x52b, 0x52d, 0x7, 
    0x5b, 0x2, 0x2, 0x52c, 0x52e, 0x7, 0x7f, 0x2, 0x2, 0x52d, 0x52c, 0x3, 
    0x2, 0x2, 0x2, 0x52d, 0x52e, 0x3, 0x2, 0x2, 0x2, 0x52e, 0x52f, 0x3, 
    0x2, 0x2, 0x2, 0x52f, 0x531, 0x7, 0x8, 0x2, 0x2, 0x530, 0x532, 0x7, 
    0x7f, 0x2, 0x2, 0x531, 0x530, 0x3, 0x2, 0x2, 0x2, 0x531, 0x532, 0x3, 
    0x2, 0x2, 0x2, 0x532, 0x533, 0x3, 0x2, 0x2, 0x2, 0x533, 0x535, 0x5, 
    0x9a, 0x4e, 0x2, 0x534, 0x536, 0x7, 0x7f, 0x2, 0x2, 0x535, 0x534, 0x3, 
    0x2, 0x2, 0x2, 0x535, 0x536, 0x3, 0x2, 0x2, 0x2, 0x536, 0x537, 0x3, 
    0x2, 0x2, 0x2, 0x537, 0x538, 0x7, 0x9, 0x2, 0x2, 0x538, 0x556, 0x3, 
    0x2, 0x2, 0x2, 0x539, 0x53b, 0x7, 0x5c, 0x2, 0x2, 0x53a, 0x53c, 0x7, 
    0x7f, 0x2, 0x2, 0x53b, 0x53a, 0x3, 0x2, 0x2, 0x2, 0x53b, 0x53c, 0x3, 
    0x2, 0x2, 0x2, 0x53c, 0x53d, 0x3, 0x2, 0x2, 0x2, 0x53d, 0x53f, 0x7, 
    0x8, 0x2, 0x2, 0x53e, 0x540, 0x7, 0x7f, 0x2, 0x2, 0x53f, 0x53e, 0x3, 
    0x2, 0x2, 0x2, 0x53f, 0x540, 0x3, 0x2, 0x2, 0x2, 0x540, 0x541, 0x3, 
    0x2, 0x2, 0x2, 0x541, 0x543, 0x5, 0x9a, 0x4e, 0x2, 0x542, 0x544, 0x7, 
    0x7f, 0x2, 0x2, 0x543, 0x542, 0x3, 0x2, 0x2, 0x2, 0x543, 0x544, 0x3, 
    0x2, 0x2, 0x2, 0x544, 0x545, 0x3, 0x2, 0x2, 0x2, 0x545, 0x546, 0x7, 
    0x9, 0x2, 0x2, 0x546, 0x556, 0x3, 0x2, 0x2, 0x2, 0x547, 0x549, 0x7, 
    0x5d, 0x2, 0x2, 0x548, 0x54a, 0x7, 0x7f, 0x2, 0x2, 0x549, 0x548, 0x3, 
    0x2, 0x2, 0x2, 0x549, 0x54a, 0x3, 0x2, 0x2, 0x2, 0x54a, 0x54b, 0x3, 
    0x2, 0x2, 0x2, 0x54b, 0x54d, 0x7, 0x8, 0x2, 0x2, 0x54c, 0x54e, 0x7, 
    0x7f, 0x2, 0x2, 0x54d, 0x54c, 0x3, 0x2, 0x2, 0x2, 0x54d, 0x54e, 0x3, 
    0x2, 0x2, 0x2, 0x54e, 0x54f, 0x3, 0x2, 0x2, 0x2, 0x54f, 0x551, 0x5, 
    0x9a, 0x4e, 0x2, 0x550, 0x552, 0x7, 0x7f, 0x2, 0x2, 0x551, 0x550, 0x3, 
    0x2, 0x2, 0x2, 0x551, 0x552, 0x3, 0x2, 0x2, 0x2, 0x552, 0x553, 0x3, 
    0x2, 0x2, 0x2, 0x553, 0x554, 0x7, 0x9, 0x2, 0x2, 0x554, 0x556, 0x3, 
    0x2, 0x2, 0x2, 0x555, 0x51d, 0x3, 0x2, 0x2, 0x2, 0x555, 0x52b, 0x3, 
    0x2, 0x2, 0x2, 0x555, 0x539, 0x3, 0x2, 0x2, 0x2, 0x555, 0x547, 0x3, 
    0x2, 0x2, 0x2, 0x556, 0x99, 0x3, 0x2, 0x2, 0x2, 0x557, 0x55c, 0x5, 0xa0, 
    0x51, 0x2, 0x558, 0x55a, 0x7, 0x7f, 0x2, 0x2, 0x559, 0x558, 0x3, 0x2, 
    0x2, 0x2, 0x559, 0x55a, 0x3, 0x2, 0x2, 0x2, 0x55a, 0x55b, 0x3, 0x2, 
    0x2, 0x2, 0x55b, 0x55d, 0x5, 0x44, 0x23, 0x2, 0x55c, 0x559, 0x3, 0x2, 
    0x2, 0x2, 0x55c, 0x55d, 0x3, 0x2, 0x2, 0x2, 0x55d, 0x9b, 0x3, 0x2, 0x2, 
    0x2, 0x55e, 0x55f, 0x5, 0x50, 0x29, 0x2, 0x55f, 0x9d, 0x3, 0x2, 0x2, 
    0x2, 0x560, 0x562, 0x7, 0x8, 0x2, 0x2, 0x561, 0x563, 0x7, 0x7f, 0x2, 
    0x2, 0x562, 0x561, 0x3, 0x2, 0x2, 0x2, 0x562, 0x563, 0x3, 0x2, 0x2, 
    0x2, 0x563, 0x564, 0x3, 0x2, 0x2, 0x2, 0x564, 0x566, 0x5, 0x6a, 0x36, 
    0x2, 0x565, 0x567, 0x7, 0x7f, 0x2, 0x2, 0x566, 0x565, 0x3, 0x2, 0x2, 
    0x2, 0x566, 0x567, 0x3, 0x2, 0x2, 0x2, 0x567, 0x568, 0x3, 0x2, 0x2, 
    0x2, 0x568, 0x569, 0x7, 0x9, 0x2, 0x2, 0x569, 0x9f, 0x3, 0x2, 0x2, 0x2, 
    0x56a, 0x56b, 0x5, 0xb2, 0x5a, 0x2, 0x56b, 0x56c, 0x7, 0x7f, 0x2, 0x2, 
    0x56c, 0x56d, 0x7, 0x52, 0x2, 0x2, 0x56d, 0x56e, 0x7, 0x7f, 0x2, 0x2, 
    0x56e, 0x56f, 0x5, 0x6a, 0x36, 0x2, 0x56f, 0xa1, 0x3, 0x2, 0x2, 0x2, 
    0x570, 0x572, 0x5, 0xa4, 0x53, 0x2, 0x571, 0x573, 0x7, 0x7f, 0x2, 0x2, 
    0x572, 0x571, 0x3, 0x2, 0x2, 0x2, 0x572, 0x573, 0x3, 0x2, 0x2, 0x2, 
    0x573, 0x574, 0x3, 0x2, 0x2, 0x2, 0x574, 0x576, 0x7, 0x8, 0x2, 0x2, 
    0x575, 0x577, 0x7, 0x7f, 0x2, 0x2, 0x576, 0x575, 0x3, 0x2, 0x2, 0x2, 
    0x576, 0x577, 0x3, 0x2, 0x2, 0x2, 0x577, 0x57c, 0x3, 0x2, 0x2, 0x2, 
    0x578, 0x57a, 0x7, 0x41, 0x2, 0x2, 0x579, 0x57b, 0x7, 0x7f, 0x2, 0x2, 
    0x57a, 0x579, 0x3, 0x2, 0x2, 0x2, 0x57a, 0x57b, 0x3, 0x2, 0x2, 0x2, 
    0x57b, 0x57d, 0x3, 0x2, 0x2, 0x2, 0x57c, 0x578, 0x3, 0x2, 0x2, 0x2, 
    0x57c, 0x57d, 0x3, 0x2, 0x2, 0x2, 0x57d, 0x58f, 0x3, 0x2, 0x2, 0x2, 
    0x57e, 0x580, 0x5, 0x6a, 0x36, 0x2, 0x57f, 0x581, 0x7, 0x7f, 0x2, 0x2, 
    0x580, 0x57f, 0x3, 0x2, 0x2, 0x2, 0x580, 0x581, 0x3, 0x2, 0x2, 0x2, 
    0x581, 0x58c, 0x3, 0x2, 0x2, 0x2, 0x582, 0x584, 0x7, 0x4, 0x2, 0x2, 
    0x583, 0x585, 0x7, 0x7f, 0x2, 0x2, 0x584, 0x583, 0x3, 0x2, 0x2, 0x2, 
    0x584, 0x585, 0x3, 0x2, 0x2, 0x2, 0x585, 0x586, 0x3, 0x2, 0x2, 0x2, 
    0x586, 0x588, 0x5, 0x6a, 0x36, 0x2, 0x587, 0x589, 0x7, 0x7f, 0x2, 0x2, 
    0x588, 0x587, 0x3, 0x2, 0x2, 0x2, 0x588, 0x589, 0x3, 0x2, 0x2, 0x2, 
    0x589, 0x58b, 0x3, 0x2, 0x2, 0x2, 0x58a, 0x582, 0x3, 0x2, 0x2, 0x2, 
    0x58b, 0x58e, 0x3, 0x2, 0x2, 0x2, 0x58c, 0x58a, 0x3, 0x2, 0x2, 0x2, 
    0x58c, 0x58d, 0x3, 0x2, 0x2, 0x2, 0x58d, 0x590, 0x3, 0x2, 0x2, 0x2, 
    0x58e, 0x58c, 0x3, 0x2, 0x2, 0x2, 0x58f, 0x57e, 0x3, 0x2, 0x2, 0x2, 
    0x58f, 0x590, 0x3, 0x2, 0x2, 0x2, 0x590, 0x591, 0x3, 0x2, 0x2, 0x2, 
    0x591, 0x592, 0x7, 0x9, 0x2, 0x2, 0x592, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x593, 
    0x594, 0x5, 0xb0, 0x59, 0x2, 0x594, 0x595, 0x5, 0xc6, 0x64, 0x2, 0x595, 
    0xa5, 0x3, 0x2, 0x2, 0x2, 0x596, 0x598, 0x7, 0x5e, 0x2, 0x2, 0x597, 
    0x599, 0x7, 0x7f, 0x2, 0x2, 0x598, 0x597, 0x3, 0x2, 0x2, 0x2, 0x598, 
    0x599, 0x3, 0x2, 0x2, 0x2, 0x599, 0x59a, 0x3, 0x2, 0x2, 0x2, 0x59a, 
    0x59c, 0x7, 0x1a, 0x2, 0x2, 0x59b, 0x59d, 0x7, 0x7f, 0x2, 0x2, 0x59c, 
    0x59b, 0x3, 0x2, 0x2, 0x2, 0x59c, 0x59d, 0x3, 0x2, 0x2, 0x2, 0x59d, 
    0x5a6, 0x3, 0x2, 0x2, 0x2, 0x59e, 0x5a7, 0x5, 0x8, 0x5, 0x2, 0x59f, 
    0x5a4, 0x5, 0x46, 0x24, 0x2, 0x5a0, 0x5a2, 0x7, 0x7f, 0x2, 0x2, 0x5a1, 
    0x5a0, 0x3, 0x2, 0x2, 0x2, 0x5a1, 0x5a2, 0x3, 0x2, 0x2, 0x2, 0x5a2, 
    0x5a3, 0x3, 0x2, 0x2, 0x2, 0x5a3, 0x5a5, 0x5, 0x44, 0x23, 0x2, 0x5a4, 
    0x5a1, 0x3, 0x2, 0x2, 0x2, 0x5a4, 0x5a5, 0x3, 0x2, 0x2, 0x2, 0x5a5, 
    0x5a7, 0x3, 0x2, 0x2, 0x2, 0x5a6, 0x59e, 0x3, 0x2, 0x2, 0x2, 0x5a6, 
    0x59f, 0x3, 0x2, 0x2, 0x2, 0x5a7, 0x5a9, 0x3, 0x2, 0x2, 0x2, 0x5a8, 
    0x5aa, 0x7, 0x7f, 0x2, 0x2, 0x5a9, 0x5a8, 0x3, 0x2, 0x2, 0x2, 0x5a9, 
    0x5aa, 0x3, 0x2, 0x2, 0x2, 0x5aa, 0x5ab, 0x3, 0x2, 0x2, 0x2, 0x5ab, 
    0x5ac, 0x7, 0x1b, 0x2, 0x2, 0x5ac, 0xa7, 0x3, 0x2, 0x2, 0x2, 0x5ad, 
    0x5af, 0x5, 0xae, 0x58, 0x2, 0x5ae, 0x5b0, 0x7, 0x7f, 0x2, 0x2, 0x5af, 
    0x5ae, 0x3, 0x2, 0x2, 0x2, 0x5af, 0x5b0, 0x3, 0x2, 0x2, 0x2, 0x5b0, 
    0x5b1, 0x3, 0x2, 0x2, 0x2, 0x5b1, 0x5b3, 0x7, 0x8, 0x2, 0x2, 0x5b2, 
    0x5b4, 0x7, 0x7f, 0x2, 0x2, 0x5b3, 0x5b2, 0x3, 0x2, 0x2, 0x2, 0x5b3, 
    0x5b4, 0x3, 0x2, 0x2, 0x2, 0x5b4, 0x5c6, 0x3, 0x2, 0x2, 0x2, 0x5b5, 
    0x5b7, 0x5, 0x6a, 0x36, 0x2, 0x5b6, 0x5b8, 0x7, 0x7f, 0x2, 0x2, 0x5b7, 
    0x5b6, 0x3, 0x2, 0x2, 0x2, 0x5b7, 0x5b8, 0x3, 0x2, 0x2, 0x2, 0x5b8, 
    0x5c3, 0x3, 0x2, 0x2, 0x2, 0x5b9, 0x5bb, 0x7, 0x4, 0x2, 0x2, 0x5ba, 
    0x5bc, 0x7, 0x7f, 0x2, 0x2, 0x5bb, 0x5ba, 0x3, 0x2, 0x2, 0x2, 0x5bb, 
    0x5bc, 0x3, 0x2, 0x2, 0x2, 0x5bc, 0x5bd, 0x3, 0x2, 0x2, 0x2, 0x5bd, 
    0x5bf, 0x5, 0x6a, 0x36, 0x2, 0x5be, 0x5c0, 0x7, 0x7f, 0x2, 0x2, 0x5bf, 
    0x5be, 0x3, 0x2, 0x2, 0x2, 0x5bf, 0x5c0, 0x3, 0x2, 0x2, 0x2, 0x5c0, 
    0x5c2, 0x3, 0x2, 0x2, 0x2, 0x5c1, 0x5b9, 0x3, 0x2, 0x2, 0x2, 0x5c2, 
    0x5c5, 0x3, 0x2, 0x2, 0x2, 0x5c3, 0x5c1, 0x3, 0x2, 0x2, 0x2, 0x5c3, 
    0x5c4, 0x3, 0x2, 0x2, 0x2, 0x5c4, 0x5c7, 0x3, 0x2, 0x2, 0x2, 0x5c5, 
    0x5c3, 0x3, 0x2, 0x2, 0x2, 0x5c6, 0x5b5, 0x3, 0x2, 0x2, 0x2, 0x5c6, 
    0x5c7, 0x3, 0x2, 0x2, 0x2, 0x5c7, 0x5c8, 0x3, 0x2, 0x2, 0x2, 0x5c8, 
    0x5c9, 0x7, 0x9, 0x2, 0x2, 0x5c9, 0xa9, 0x3, 0x2, 0x2, 0x2, 0x5ca, 0x5cb, 
    0x5, 0xae, 0x58, 0x2, 0x5cb, 0xab, 0x3, 0x2, 0x2, 0x2, 0x5cc, 0x5cd, 
    0x5, 0xca, 0x66, 0x2, 0x5cd, 0xad, 0x3, 0x2, 0x2, 0x2, 0x5ce, 0x5cf, 
    0x5, 0xb0, 0x59, 0x2, 0x5cf, 0x5d0, 0x5, 0xc6, 0x64, 0x2, 0x5d0, 0xaf, 
    0x3, 0x2, 0x2, 0x2, 0x5d1, 0x5d2, 0x5, 0xc6, 0x64, 0x2, 0x5d2, 0x5d3, 
    0x7, 0x19, 0x2, 0x2, 0x5d3, 0x5d5, 0x3, 0x2, 0x2, 0x2, 0x5d4, 0x5d1, 
    0x3, 0x2, 0x2, 0x2, 0x5d5, 0x5d8, 0x3, 0x2, 0x2, 0x2, 0x5d6, 0x5d4, 
    0x3, 0x2, 0x2, 0x2, 0x5d6, 0x5d7, 0x3, 0x2, 0x2, 0x2, 0x5d7, 0xb1, 0x3, 
    0x2, 0x2, 0x2, 0x5d8, 0x5d6, 0x3, 0x2, 0x2, 0x2, 0x5d9, 0x5da, 0x5, 
    0xca, 0x66, 0x2, 0x5da, 0xb3, 0x3, 0x2, 0x2, 0x2, 0x5db, 0x5e2, 0x5, 
    0xb6, 0x5c, 0x2, 0x5dc, 0x5e2, 0x7, 0x54, 0x2, 0x2, 0x5dd, 0x5e2, 0x5, 
    0xb8, 0x5d, 0x2, 0x5de, 0x5e2, 0x7, 0x6d, 0x2, 0x2, 0x5df, 0x5e2, 0x5, 
    0xbe, 0x60, 0x2, 0x5e0, 0x5e2, 0x5, 0xc0, 0x61, 0x2, 0x5e1, 0x5db, 0x3, 
    0x2, 0x2, 0x2, 0x5e1, 0x5dc, 0x3, 0x2, 0x2, 0x2, 0x5e1, 0x5dd, 0x3, 
    0x2, 0x2, 0x2, 0x5e1, 0x5de, 0x3, 0x2, 0x2, 0x2, 0x5e1, 0x5df, 0x3, 
    0x2, 0x2, 0x2, 0x5e1, 0x5e0, 0x3, 0x2, 0x2, 0x2, 0x5e2, 0xb5, 0x3, 0x2, 
    0x2, 0x2, 0x5e3, 0x5e4, 0x9, 0x4, 0x2, 0x2, 0x5e4, 0xb7, 0x3, 0x2, 0x2, 
    0x2, 0x5e5, 0x5e8, 0x5, 0xbc, 0x5f, 0x2, 0x5e6, 0x5e8, 0x5, 0xba, 0x5e, 
    0x2, 0x5e7, 0x5e5, 0x3, 0x2, 0x2, 0x2, 0x5e7, 0x5e6, 0x3, 0x2, 0x2, 
    0x2, 0x5e8, 0xb9, 0x3, 0x2, 0x2, 0x2, 0x5e9, 0x5ea, 0x9, 0x5, 0x2, 0x2, 
    0x5ea, 0xbb, 0x3, 0x2, 0x2, 0x2, 0x5eb, 0x5ec, 0x9, 0x6, 0x2, 0x2, 0x5ec, 
    0xbd, 0x3, 0x2, 0x2, 0x2, 0x5ed, 0x5ef, 0x7, 0xa, 0x2, 0x2, 0x5ee, 0x5f0, 
    0x7, 0x7f, 0x2, 0x2, 0x5ef, 0x5ee, 0x3, 0x2, 0x2, 0x2, 0x5ef, 0x5f0, 
    0x3, 0x2, 0x2, 0x2, 0x5f0, 0x602, 0x3, 0x2, 0x2, 0x2, 0x5f1, 0x5f3, 
    0x5, 0x6a, 0x36, 0x2, 0x5f2, 0x5f4, 0x7, 0x7f, 0x2, 0x2, 0x5f3, 0x5f2, 
    0x3, 0x2, 0x2, 0x2, 0x5f3, 0x5f4, 0x3, 0x2, 0x2, 0x2, 0x5f4, 0x5ff, 
    0x3, 0x2, 0x2, 0x2, 0x5f5, 0x5f7, 0x7, 0x4, 0x2, 0x2, 0x5f6, 0x5f8, 
    0x7, 0x7f, 0x2, 0x2, 0x5f7, 0x5f6, 0x3, 0x2, 0x2, 0x2, 0x5f7, 0x5f8, 
    0x3, 0x2, 0x2, 0x2, 0x5f8, 0x5f9, 0x3, 0x2, 0x2, 0x2, 0x5f9, 0x5fb, 
    0x5, 0x6a, 0x36, 0x2, 0x5fa, 0x5fc, 0x7, 0x7f, 0x2, 0x2, 0x5fb, 0x5fa, 
    0x3, 0x2, 0x2, 0x2, 0x5fb, 0x5fc, 0x3, 0x2, 0x2, 0x2, 0x5fc, 0x5fe, 
    0x3, 0x2, 0x2, 0x2, 0x5fd, 0x5f5, 0x3, 0x2, 0x2, 0x2, 0x5fe, 0x601, 
    0x3, 0x2, 0x2, 0x2, 0x5ff, 0x5fd, 0x3, 0x2, 0x2, 0x2, 0x5ff, 0x600, 
    0x3, 0x2, 0x2, 0x2, 0x600, 0x603, 0x3, 0x2, 0x2, 0x2, 0x601, 0x5ff, 
    0x3, 0x2, 0x2, 0x2, 0x602, 0x5f1, 0x3, 0x2, 0x2, 0x2, 0x602, 0x603, 
    0x3, 0x2, 0x2, 0x2, 0x603, 0x604, 0x3, 0x2, 0x2, 0x2, 0x604, 0x605, 
    0x7, 0xb, 0x2, 0x2, 0x605, 0xbf, 0x3, 0x2, 0x2, 0x2, 0x606, 0x608, 0x7, 
    0x1a, 0x2, 0x2, 0x607, 0x609, 0x7, 0x7f, 0x2, 0x2, 0x608, 0x607, 0x3, 
    0x2, 0x2, 0x2, 0x608, 0x609, 0x3, 0x2, 0x2, 0x2, 0x609, 0x62b, 0x3, 
    0x2, 0x2, 0x2, 0x60a, 0x60c, 0x5, 0xc2, 0x62, 0x2, 0x60b, 0x60d, 0x7, 
    0x7f, 0x2, 0x2, 0x60c, 0x60b, 0x3, 0x2, 0x2, 0x2, 0x60c, 0x60d, 0x3, 
    0x2, 0x2, 0x2, 0x60d, 0x60e, 0x3, 0x2, 0x2, 0x2, 0x60e, 0x610, 0x7, 
    0xc, 0x2, 0x2, 0x60f, 0x611, 0x7, 0x7f, 0x2, 0x2, 0x610, 0x60f, 0x3, 
    0x2, 0x2, 0x2, 0x610, 0x611, 0x3, 0x2, 0x2, 0x2, 0x611, 0x612, 0x3, 
    0x2, 0x2, 0x2, 0x612, 0x614, 0x5, 0x6a, 0x36, 0x2, 0x613, 0x615, 0x7, 
    0x7f, 0x2, 0x2, 0x614, 0x613, 0x3, 0x2, 0x2, 0x2, 0x614, 0x615, 0x3, 
    0x2, 0x2, 0x2, 0x615, 0x628, 0x3, 0x2, 0x2, 0x2, 0x616, 0x618, 0x7, 
    0x4, 0x2, 0x2, 0x617, 0x619, 0x7, 0x7f, 0x2, 0x2, 0x618, 0x617, 0x3, 
    0x2, 0x2, 0x2, 0x618, 0x619, 0x3, 0x2, 0x2, 0x2, 0x619, 0x61a, 0x3, 
    0x2, 0x2, 0x2, 0x61a, 0x61c, 0x5, 0xc2, 0x62, 0x2, 0x61b, 0x61d, 0x7, 
    0x7f, 0x2, 0x2, 0x61c, 0x61b, 0x3, 0x2, 0x2, 0x2, 0x61c, 0x61d, 0x3, 
    0x2, 0x2, 0x2, 0x61d, 0x61e, 0x3, 0x2, 0x2, 0x2, 0x61e, 0x620, 0x7, 
    0xc, 0x2, 0x2, 0x61f, 0x621, 0x7, 0x7f, 0x2, 0x2, 0x620, 0x61f, 0x3, 
    0x2, 0x2, 0x2, 0x620, 0x621, 0x3, 0x2, 0x2, 0x2, 0x621, 0x622, 0x3, 
    0x2, 0x2, 0x2, 0x622, 0x624, 0x5, 0x6a, 0x36, 0x2, 0x623, 0x625, 0x7, 
    0x7f, 0x2, 0x2, 0x624, 0x623, 0x3, 0x2, 0x2, 0x2, 0x624, 0x625, 0x3, 
    0x2, 0x2, 0x2, 0x625, 0x627, 0x3, 0x2, 0x2, 0x2, 0x626, 0x616, 0x3, 
    0x2, 0x2, 0x2, 0x627, 0x62a, 0x3, 0x2, 0x2, 0x2, 0x628, 0x626, 0x3, 
    0x2, 0x2, 0x2, 0x628, 0x629, 0x3, 0x2, 0x2, 0x2, 0x629, 0x62c, 0x3, 
    0x2, 0x2, 0x2, 0x62a, 0x628, 0x3, 0x2, 0x2, 0x2, 0x62b, 0x60a, 0x3, 
    0x2, 0x2, 0x2, 0x62b, 0x62c, 0x3, 0x2, 0x2, 0x2, 0x62c, 0x62d, 0x3, 
    0x2, 0x2, 0x2, 0x62d, 0x62e, 0x7, 0x1b, 0x2, 0x2, 0x62e, 0xc1, 0x3, 
    0x2, 0x2, 0x2, 0x62f, 0x630, 0x5, 0xc6, 0x64, 0x2, 0x630, 0xc3, 0x3, 
    0x2, 0x2, 0x2, 0x631, 0x634, 0x7, 0x1c, 0x2, 0x2, 0x632, 0x635, 0x5, 
    0xca, 0x66, 0x2, 0x633, 0x635, 0x7, 0x62, 0x2, 0x2, 0x634, 0x632, 0x3, 
    0x2, 0x2, 0x2, 0x634, 0x633, 0x3, 0x2, 0x2, 0x2, 0x635, 0xc5, 0x3, 0x2, 
    0x2, 0x2, 0x636, 0x639, 0x5, 0xca, 0x66, 0x2, 0x637, 0x639, 0x5, 0xc8, 
    0x65, 0x2, 0x638, 0x636, 0x3, 0x2, 0x2, 0x2, 0x638, 0x637, 0x3, 0x2, 
    0x2, 0x2, 0x639, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x63a, 0x63b, 0x9, 0x7, 0x2, 
    0x2, 0x63b, 0xc9, 0x3, 0x2, 0x2, 0x2, 0x63c, 0x63d, 0x9, 0x8, 0x2, 0x2, 
    0x63d, 0xcb, 0x3, 0x2, 0x2, 0x2, 0x63e, 0x63f, 0x9, 0x9, 0x2, 0x2, 0x63f, 
    0xcd, 0x3, 0x2, 0x2, 0x2, 0x640, 0x641, 0x9, 0xa, 0x2, 0x2, 0x641, 0xcf, 
    0x3, 0x2, 0x2, 0x2, 0x642, 0x643, 0x9, 0xb, 0x2, 0x2, 0x643, 0xd1, 0x3, 
    0x2, 0x2, 0x2, 0x12c, 0xd3, 0xd7, 0xda, 0xdd, 0xe5, 0xe9, 0xee, 0xf5, 
    0xfa, 0xfd, 0x101, 0x105, 0x109, 0x10f, 0x113, 0x118, 0x11d, 0x121, 
    0x124, 0x126, 0x12a, 0x12e, 0x133, 0x137, 0x13c, 0x140, 0x149, 0x14e, 
    0x152, 0x156, 0x15a, 0x15d, 0x161, 0x16b, 0x172, 0x17f, 0x183, 0x189, 
    0x18d, 0x191, 0x196, 0x19b, 0x19f, 0x1a5, 0x1a9, 0x1af, 0x1b3, 0x1b9, 
    0x1bd, 0x1c1, 0x1c5, 0x1c9, 0x1cd, 0x1d2, 0x1d9, 0x1dd, 0x1e2, 0x1e9, 
    0x1ef, 0x1f4, 0x1fa, 0x1fd, 0x203, 0x205, 0x209, 0x20d, 0x212, 0x216, 
    0x219, 0x220, 0x227, 0x22a, 0x230, 0x233, 0x239, 0x23d, 0x241, 0x245, 
    0x249, 0x24e, 0x253, 0x257, 0x25c, 0x25f, 0x268, 0x271, 0x276, 0x283, 
    0x286, 0x28e, 0x292, 0x297, 0x29c, 0x2a0, 0x2a5, 0x2a9, 0x2ad, 0x2b1, 
    0x2b6, 0x2ba, 0x2bf, 0x2c4, 0x2c9, 0x2cb, 0x2cf, 0x2d4, 0x2d8, 0x2dc, 
    0x2de, 0x2e2, 0x2e4, 0x2e8, 0x2ea, 0x2f0, 0x2f6, 0x2fa, 0x2fd, 0x300, 
    0x304, 0x30a, 0x30e, 0x311, 0x314, 0x31a, 0x31d, 0x320, 0x324, 0x32a, 
    0x32d, 0x330, 0x334, 0x338, 0x33c, 0x33e, 0x342, 0x344, 0x347, 0x34b, 
    0x34d, 0x353, 0x357, 0x35b, 0x35f, 0x362, 0x367, 0x36c, 0x371, 0x376, 
    0x37c, 0x380, 0x382, 0x386, 0x38a, 0x38c, 0x38e, 0x396, 0x39b, 0x3a6, 
    0x3b0, 0x3ba, 0x3bf, 0x3c3, 0x3ca, 0x3cf, 0x3d4, 0x3d9, 0x3de, 0x3e3, 
    0x3e8, 0x3ed, 0x3f0, 0x3f6, 0x3f8, 0x405, 0x408, 0x40f, 0x41d, 0x421, 
    0x425, 0x429, 0x42d, 0x430, 0x432, 0x437, 0x43b, 0x43f, 0x443, 0x447, 
    0x44b, 0x44e, 0x450, 0x455, 0x459, 0x45e, 0x464, 0x467, 0x46b, 0x472, 
    0x476, 0x47a, 0x47d, 0x47f, 0x484, 0x489, 0x48d, 0x490, 0x494, 0x49d, 
    0x4a1, 0x4a5, 0x4b0, 0x4b4, 0x4b9, 0x4bd, 0x4c1, 0x4c6, 0x4c8, 0x4cb, 
    0x4cf, 0x4d2, 0x4d5, 0x4db, 0x4df, 0x4e3, 0x4e9, 0x4ed, 0x4f1, 0x4f4, 
    0x4f7, 0x4fd, 0x501, 0x505, 0x507, 0x50b, 0x50f, 0x511, 0x515, 0x519, 
    0x51f, 0x523, 0x527, 0x52d, 0x531, 0x535, 0x53b, 0x53f, 0x543, 0x549, 
    0x54d, 0x551, 0x555, 0x559, 0x55c, 0x562, 0x566, 0x572, 0x576, 0x57a, 
    0x57c, 0x580, 0x584, 0x588, 0x58c, 0x58f, 0x598, 0x59c, 0x5a1, 0x5a4, 
    0x5a6, 0x5a9, 0x5af, 0x5b3, 0x5b7, 0x5bb, 0x5bf, 0x5c3, 0x5c6, 0x5d6, 
    0x5e1, 0x5e7, 0x5ef, 0x5f3, 0x5f7, 0x5fb, 0x5ff, 0x602, 0x608, 0x60c, 
    0x610, 0x614, 0x618, 0x61c, 0x620, 0x624, 0x628, 0x62b, 0x634, 0x638, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CypherParser::Initializer CypherParser::_init;
