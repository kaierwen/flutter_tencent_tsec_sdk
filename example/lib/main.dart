import 'dart:async';

import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:flutter_tencent_tsec_sdk/tencent_tsec_sdk.dart';

void main() {
  runApp(MyApp());
}

class MyApp extends StatefulWidget {
  const MyApp({super.key});

  @override
  _MyAppState createState() => _MyAppState();
}

class _MyAppState extends State<MyApp> {
  final _tsecSdk = TencentTsecSdk();
  final _scaffoldMessengerKey = GlobalKey<ScaffoldMessengerState>();
  bool _sdkInitialized = false;
  String? _platformVersion;
  String? _deviceToken;
  String? _errorMessage;

  @override
  void initState() {
    super.initState();
    _initializeSdk();
  }

  Future<void> _initializeSdk() async {
    try {
      // 调用原生方法初始化SDK，channel根据腾讯云后台获取，
      // 参考[快速入门 - 步骤5：生成 SDK_channel](https://cloud.tencent.com/document/product/1628/79610#cee40935-2ef8-4500-bb4e-f6c0a5742c34)
      final bool success = await _tsecSdk.initialize(
        channel: 1,
        enableLog: true,
      );
      if (success) {
        final version = await _tsecSdk.getPlatformVersion();
        setState(() {
          _sdkInitialized = true;
          _platformVersion = version;
          _errorMessage = null;
        });
      } else {
        setState(() {
          _sdkInitialized = false;
          _errorMessage = '初始化失败';
        });
      }
    } catch (e) {
      setState(() {
        _sdkInitialized = false;
        _errorMessage = '初始化出错: $e';
      });
    }
  }

  Future<void> _getDeviceToken() async {
    try {
      setState(() {
        _errorMessage = null;
        _deviceToken = null;
      });
      final token = await _tsecSdk.getDeviceToken();
      if (token != null && token.isNotEmpty) {
        if (token.startsWith('errorCode:')) {
          setState(() {
            _errorMessage = '获取设备Token失败: $token';
            _deviceToken = token;
          });
        } else {
          setState(() {
            _deviceToken = token;
            _errorMessage = null;
          });
        }
      } else {
        setState(() {
          _errorMessage = '获取设备Token失败';
          _deviceToken = null;
        });
      }
    } catch (e) {
      setState(() {
        _errorMessage = '获取设备Token出错: $e';
        _deviceToken = null;
      });
    }
  }

  Future<void> _copyToClipboard(String text) async {
    if (text.isEmpty) return;
    await Clipboard.setData(ClipboardData(text: text));
    if (mounted && _scaffoldMessengerKey.currentState != null) {
      _scaffoldMessengerKey.currentState!.showSnackBar(
        const SnackBar(
          content: Row(
            children: [
              Icon(Icons.check_circle, color: Colors.white, size: 20),
              SizedBox(width: 8),
              Text('已复制到剪切板'),
            ],
          ),
          duration: Duration(seconds: 2),
          backgroundColor: Colors.green,
        ),
      );
    }
  }

  @override
  Widget build(BuildContext context) {
    return _buildApp(context);
  }

  /// 构建整个应用
  Widget _buildApp(BuildContext context) {
    return MaterialApp(
      scaffoldMessengerKey: _scaffoldMessengerKey,
      home: _buildScaffold(context),
    );
  }

  /// 构建 Scaffold
  Widget _buildScaffold(BuildContext context) {
    return Scaffold(
      appBar: AppBar(
        title: const Text('tencent tsec sdk example'),
        elevation: 2,
      ),
      body: _buildBody(context),
    );
  }

  /// 构建页面主体内容
  Widget _buildBody(BuildContext context) {
    return SingleChildScrollView(
      padding: const EdgeInsets.all(16.0),
      child: Column(
        crossAxisAlignment: CrossAxisAlignment.stretch,
        children: [
          const SizedBox(height: 8),
          _buildVersionCard(context),
          const SizedBox(height: 16),
          _buildStatusCard(context),
          const SizedBox(height: 16),
          _buildActionButton(context),
          const SizedBox(height: 24),
          _buildTokenCard(context),
          const SizedBox(height: 16),
          if (_errorMessage != null && _errorMessage != '无')
            _buildErrorCard(context),
          const SizedBox(height: 16),
        ],
      ),
    );
  }

  /// 构建 SDK 版本信息卡片
  Widget _buildVersionCard(BuildContext context) {
    return Card(
      elevation: 2,
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Icon(
                  Icons.info_outline,
                  color: Theme.of(context).primaryColor,
                  size: 20,
                ),
                const SizedBox(width: 8),
                const Text(
                  'SDK版本',
                  style: TextStyle(
                    fontSize: 14,
                    fontWeight: FontWeight.w500,
                    color: Colors.grey,
                  ),
                ),
              ],
            ),
            const SizedBox(height: 8),
            Text(
              _platformVersion ?? '未知',
              style: const TextStyle(fontSize: 16, fontWeight: FontWeight.bold),
            ),
          ],
        ),
      ),
    );
  }

  /// 构建 SDK 状态卡片
  Widget _buildStatusCard(BuildContext context) {
    final statusColor = _sdkInitialized ? Colors.green : Colors.orange;
    final statusIcon = _sdkInitialized
        ? Icons.check_circle
        : Icons.error_outline;
    final statusText = _sdkInitialized ? '已就绪' : '未初始化';

    return Card(
      elevation: 2,
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Icon(statusIcon, color: statusColor, size: 20),
                const SizedBox(width: 8),
                const Text(
                  'SDK状态',
                  style: TextStyle(
                    fontSize: 14,
                    fontWeight: FontWeight.w500,
                    color: Colors.grey,
                  ),
                ),
              ],
            ),
            const SizedBox(height: 8),
            Row(
              children: [
                Container(
                  width: 12,
                  height: 12,
                  decoration: BoxDecoration(
                    shape: BoxShape.circle,
                    color: statusColor,
                  ),
                ),
                const SizedBox(width: 8),
                Text(
                  statusText,
                  style: TextStyle(
                    fontSize: 16,
                    fontWeight: FontWeight.bold,
                    color: statusColor,
                  ),
                ),
              ],
            ),
          ],
        ),
      ),
    );
  }

  /// 构建操作按钮
  Widget _buildActionButton(BuildContext context) {
    return ElevatedButton.icon(
      onPressed: _sdkInitialized ? _getDeviceToken : null,
      icon: const Icon(Icons.refresh),
      label: const Text('获取设备Token'),
      style: ElevatedButton.styleFrom(
        padding: const EdgeInsets.symmetric(vertical: 16),
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(8)),
      ),
    );
  }

  /// 构建设备 Token 卡片
  Widget _buildTokenCard(BuildContext context) {
    return Card(
      elevation: 2,
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            _buildTokenHeader(context),
            const SizedBox(height: 12),
            _buildTokenContent(context),
          ],
        ),
      ),
    );
  }

  /// 构建 Token 卡片头部（标题和复制按钮）
  Widget _buildTokenHeader(BuildContext context) {
    return Row(
      mainAxisAlignment: MainAxisAlignment.spaceBetween,
      children: [
        Row(
          children: [
            Icon(
              Icons.fingerprint,
              color: Theme.of(context).primaryColor,
              size: 20,
            ),
            const SizedBox(width: 8),
            const Text(
              '设备Token',
              style: TextStyle(
                fontSize: 14,
                fontWeight: FontWeight.w500,
                color: Colors.grey,
              ),
            ),
          ],
        ),
        if (_deviceToken != null && _deviceToken!.isNotEmpty)
          IconButton(
            icon: const Icon(Icons.copy, size: 20),
            onPressed: () => _copyToClipboard(_deviceToken!),
            tooltip: '复制到剪切板',
            padding: EdgeInsets.zero,
            constraints: const BoxConstraints(),
            color: Theme.of(context).primaryColor,
          ),
      ],
    );
  }

  /// 构建 Token 内容区域
  Widget _buildTokenContent(BuildContext context) {
    final hasToken = _deviceToken != null && _deviceToken!.isNotEmpty;

    return GestureDetector(
      onTap: hasToken ? () => _copyToClipboard(_deviceToken!) : null,
      child: Container(
        width: double.infinity,
        padding: const EdgeInsets.all(12),
        decoration: BoxDecoration(
          color: Colors.grey[100],
          borderRadius: BorderRadius.circular(8),
          border: Border.all(color: Colors.grey[300]!),
        ),
        child: hasToken
            ? Row(
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Expanded(
                    child: SelectableText(
                      _deviceToken!,
                      style: const TextStyle(
                        fontSize: 13,
                        fontFamily: 'monospace',
                        height: 1.5,
                      ),
                    ),
                  ),
                  const SizedBox(width: 8),
                  Icon(Icons.content_copy, size: 16, color: Colors.grey[600]),
                ],
              )
            : Text(
                '点击上方按钮获取设备Token',
                style: TextStyle(
                  fontSize: 13,
                  color: Colors.grey[600],
                  fontStyle: FontStyle.italic,
                ),
              ),
      ),
    );
  }

  /// 构建错误信息卡片
  Widget _buildErrorCard(BuildContext context) {
    return Card(
      elevation: 2,
      color: Colors.red[50],
      child: Padding(
        padding: const EdgeInsets.all(16.0),
        child: Column(
          crossAxisAlignment: CrossAxisAlignment.start,
          children: [
            Row(
              children: [
                Icon(Icons.error_outline, color: Colors.red[700], size: 20),
                const SizedBox(width: 8),
                Text(
                  '错误信息',
                  style: TextStyle(
                    fontSize: 14,
                    fontWeight: FontWeight.w500,
                    color: Colors.red[700],
                  ),
                ),
              ],
            ),
            const SizedBox(height: 8),
            Text(
              _errorMessage!,
              style: TextStyle(
                fontSize: 14,
                color: Colors.red[700],
                height: 1.5,
              ),
              softWrap: true,
            ),
          ],
        ),
      ),
    );
  }
}
